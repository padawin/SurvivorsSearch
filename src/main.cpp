#include "Game.hpp"
#include "renderer/NCursesRenderer.hpp"
#include "StateMachine.hpp"
#include "state/InGame.hpp"
#include <locale.h>

int main() {
	setlocale(LC_ALL,"");
	time_t t;
	srand((unsigned int) time(&t));
	NCursesRenderer renderer;
	StateMachine stateMachine = StateMachine();
	stateMachine.pushState(new InGame());
	Game g = Game(stateMachine, &renderer);
	if (g.init()) {
		g.mainLoop();
	}

	g.shutdown();
	return 0;
}
