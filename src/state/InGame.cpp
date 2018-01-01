#include "InGame.hpp"
#include "../StateMachine.hpp"
#include "../Save.hpp"
#include "../renderData.hpp"

InGame::InGame() : m_player(Player()), m_city(City()) {
	m_viewCity.x = 0;
	m_viewCity.y = 0;
	m_viewCity.width = 79;
	m_viewCity.height = 29;
}

std::string InGame::getStateID() const {
	return "TestState";
}

bool InGame::onEnter() {
	if (!Save::exists()) {
		Save::clean();
		Save::create();
	}

	Save::load(m_player, m_city);
	return true;
}

void InGame::update(StateMachine &stateMachine) {
	int ch = getch();
	switch(ch) {
		case KEY_UP:
			m_iY -= 1;
			break;
		case KEY_DOWN:
			m_iY += 1;
			break;
		case KEY_LEFT:
			m_iX -= 1;
			break;
		case KEY_RIGHT:
			m_iX += 1;
			break;
		case 27:
			stateMachine.clean();
			break;
		default:
			break;
	}
}

void InGame::render() {
	mvaddstr(m_iY, m_iX, "Hello World");
	refresh();
}
