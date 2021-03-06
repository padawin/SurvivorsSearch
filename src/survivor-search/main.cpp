#include "../game/Game.hpp"
#include "../game/StateMachine.hpp"
#include "../game/UserActions.hpp"
#include "../game/script/Script.hpp"
#include "../game/Dialogue.hpp"
#include "../game/DialogueParser.hpp"
#include "../ncurses/Renderer.hpp"
#include "../ncurses/InputHandler.hpp"
#include "state/InGame.hpp"
#include <locale.h>
#include <memory>
#include <limits.h>
#include <libgen.h>

int main(int argc, char* args[]) {
	setlocale(LC_ALL,"");
	time_t t;
	srand((unsigned int) time(&t));
	std::shared_ptr<Renderer> renderer(new NCursesRenderer());
	std::shared_ptr<InputHandler> inputHandler(new NCursesInputHandler());
	UserActions userActions(inputHandler);
	char binaryPath[PATH_MAX];
	{
		char *res = realpath(dirname(args[argc - argc]), binaryPath);
		if (!res) {
			return 1;
		}
	}

	{
		std::string controlsMapping = std::string(binaryPath) + "/config/playercontrolsmapping.txt";
		int actionsSet = userActions.setActionsFromFile(controlsMapping.c_str());
		if (actionsSet != 0) {
			return actionsSet;
		}
	}

	Script::setScriptPath(std::string(binaryPath) + "/scripts/");
	Dialogue dialogues = Dialogue();
	{
		DialogueParser dialogParser(dialogues);
		std::string dialoguesFile = std::string(binaryPath) + "/data/dialogues.txt";
		E_FileParsingResult res = dialogParser.parseFile(dialoguesFile.c_str());
		if (res != OK) {
			return res;
		}
	}

	StateMachine stateMachine = StateMachine();
	stateMachine.pushState(new InGame(userActions, dialogues));
	Game g(stateMachine, renderer, inputHandler);
	if (g.init(binaryPath)) {
		g.mainLoop();
	}

	g.shutdown();
	return 0;
}
