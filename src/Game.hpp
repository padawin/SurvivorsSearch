#ifndef __GAME__
#define __GAME__

#include "StateMachine.hpp"
#include "renderer/Renderer.hpp"
#include <memory>

class Game {
	private:
	bool m_bIsRunning = false;
	StateMachine m_stateMachine;
	std::shared_ptr<Renderer> m_renderer;

	public:
	Game(StateMachine stateMachine, std::shared_ptr<Renderer> renderer);
	~Game() { }
	bool init();
	void mainLoop();
	void loopFrame();
	void shutdown() const;
};

#endif
