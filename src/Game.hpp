#ifndef __GAME__
#define __GAME__

#include "StateMachine.hpp"
#include "renderer/Renderer.hpp"
#include <memory>
#include <limits.h>

class Game {
	private:
	bool m_bIsRunning = false;
	char m_sBinaryPath[PATH_MAX];
	StateMachine m_stateMachine;
	std::shared_ptr<Renderer> m_renderer;

	public:
	Game(StateMachine stateMachine, std::shared_ptr<Renderer> renderer);
	~Game() { }
	bool init(char binaryPath[PATH_MAX]);
	void mainLoop();
	void loopFrame();
	void shutdown() const;
	const char* getBinaryPath() const;
};

#endif
