#include <SDL2/SDL.h>
#include "../Game.hpp"
#include "../script/Script.hpp"
#include "../globals.hpp"
#include "../Dialogue.hpp"
#include "../DialogueParser.hpp"
#include "scene/Play.hpp"
#include <memory> // shared_ptr
#include <libgen.h> // dirname
#include "sdl2/InputHandler.hpp"
#include "sdl2/Renderer.hpp"

int main(int argc, char* args[]) {
	setlocale(LC_ALL,"");
	time_t t;
	srand((unsigned int) time(&t));
	std::shared_ptr<SDL2Renderer> renderer(new SDL2Renderer());
	renderer->setWindowInfo("rRpg", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	std::shared_ptr<SDL2InputHandler> inputHandler(new SDL2InputHandler());
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
	stateMachine.pushState(new PlayScene(userActions));
	Game g(stateMachine, renderer, inputHandler);
	if (g.init(binaryPath)) {
		g.mainLoop();
	}

	g.shutdown();
	return 0;
}
