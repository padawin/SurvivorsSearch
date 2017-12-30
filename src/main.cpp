#include "Game.hpp"
#include "renderer/NCursesRenderer.hpp"
#include "StateMachine.hpp"

int main() {
	NCursesRenderer renderer;
	StateMachine stateMachine = StateMachine();
	Game g = Game(stateMachine, &renderer);
	if (g.init()) {
		g.mainLoop();
	}

	g.shutdown();
	return 0;
}
