#include "Game.hpp"

Game::Game(StateMachine stateMachine, Renderer* renderer) :
	m_stateMachine(stateMachine),
	m_renderer(renderer)
{
}

Game::Game(const Game &g) :
	m_stateMachine(g.m_stateMachine),
	m_renderer(g.m_renderer)
{
}

Game& Game::operator=(const Game &g) {
	if (this == &g) {
		return *this;
	}

	m_stateMachine = g.m_stateMachine;
	m_renderer = g.m_renderer;
	return *this;
}

bool Game::init() {
	bool res;
	time_t t;
	srand((unsigned int) time(&t));
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
