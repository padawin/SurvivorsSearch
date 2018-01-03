#include "Game.hpp"
#include <string.h>

Game::Game(StateMachine stateMachine, std::shared_ptr<Renderer> renderer) :
	m_stateMachine(stateMachine),
	m_renderer(renderer)
{
}

bool Game::init(char binaryPath[PATH_MAX]) {
	bool res;
	strncpy(m_sBinaryPath, binaryPath, PATH_MAX);
	res = m_renderer->init();
	m_bIsRunning = res;
	return res;
}

void Game::mainLoop() {
	while (m_stateMachine.getCurrentState() != NULL) {
		m_renderer->frame(this);
	}
}

void Game::loopFrame() {
	m_stateMachine.update();
	m_stateMachine.render();
}

void Game::shutdown() const {
	m_renderer->shutdown();
}

const char* Game::getBinaryPath() const {
	return m_sBinaryPath;
}
