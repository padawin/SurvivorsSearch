#include "Game.hpp"
#include "renderer/NCursesRenderer.hpp"
#include "StateMachine.hpp"
#include "state/InGame.hpp"
#include <locale.h>
#include <memory>

int main() {
	setlocale(LC_ALL,"");
	time_t t;
	srand((unsigned int) time(&t));
	std::shared_ptr<Renderer> renderer(new NCursesRenderer());
	StateMachine stateMachine = StateMachine();
	stateMachine.pushState(new InGame());
	Game g(stateMachine, renderer);
	if (g.init()) {
		g.mainLoop();
	}

	g.shutdown();
	return 0;
}
