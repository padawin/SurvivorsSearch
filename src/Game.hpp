#ifndef __GAME__
#define __GAME__

#include "StateMachine.hpp"
#include "renderer/Renderer.hpp"

class Game {
	private:
	bool m_bIsRunning = false;
	StateMachine m_stateMachine;
	Renderer* m_renderer;

	public:
	Game(const Game &r);
	Game& operator=(const Game &g);
	Game(StateMachine stateMachine, Renderer* renderer);
	bool init();
	void mainLoop();
	void loopFrame();
	void shutdown() const;
};

#endif
