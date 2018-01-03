#include "Game.hpp"
#include "ncurses/Renderer.hpp"
#include "ncurses/InputHandler.hpp"
#include "StateMachine.hpp"
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
	char binaryPath[PATH_MAX];
	char *res = realpath(dirname(args[argc - argc]), binaryPath);
	if (!res) {
		return 1;
	}

	StateMachine stateMachine = StateMachine();
	stateMachine.pushState(new InGame());
	Game g(stateMachine, renderer, inputHandler);
	if (g.init(binaryPath)) {
		g.mainLoop();
	}

	g.shutdown();
	return 0;
}
