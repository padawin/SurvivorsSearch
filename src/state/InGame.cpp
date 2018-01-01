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
	// coordinates in the world
	int topLeftX = m_player.getLocation().x - m_viewCity.width / 2,
		topLeftY = m_player.getLocation().y - m_viewCity.height / 2,
		bottomRightX = m_player.getLocation().x + m_viewCity.width / 2,
		bottomRightY = m_player.getLocation().y + m_viewCity.height / 2;
	for (int y = topLeftY; y < bottomRightY; ++y) {
		for (int x = topLeftX; x < bottomRightX; ++x) {
			mvaddstr(
				m_viewCity.y + y - topLeftY,
				m_viewCity.x + x - topLeftX,
				_getCellDisplayValue(x, y)
			);
		}
	}
	refresh();
}

const char* InGame::_getCellDisplayValue(int x, int y) {
	if (x < 0 || x > CITY_WIDTH || y < 0 || y * CITY_WIDTH > CITY_SIZE) {
		return " ";
	}

	return MAP_TILES[m_city.getCell(x, y)];
}
