#include "InGame.hpp"
#include "../StateMachine.hpp"
#include "../Save.hpp"
#include "../renderer/NCursesActor.hpp"

InGame::InGame() :
	m_player(Actor()),
	m_city(City()),
	m_cityRenderer(NCursesMap())
{
	m_player.setRenderer(new NCursesActor('@'));
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
	m_city.addActor(&m_player);
	return true;
}

void InGame::update(StateMachine &stateMachine) {
	int ch = getch();
	S_Coordinates location = m_player.getLocation();

	switch(ch) {
		case KEY_UP:
			m_city.moveActor(&m_player, location.x, location.y - 1);
			break;
		case KEY_DOWN:
			m_city.moveActor(&m_player, location.x, location.y + 1);
			break;
		case KEY_LEFT:
			m_city.moveActor(&m_player, location.x - 1, location.y);
			break;
		case KEY_RIGHT:
			m_city.moveActor(&m_player, location.x + 1, location.y);
			break;
		case 27:
			stateMachine.clean();
			break;
		default:
			break;
	}
}

void InGame::render() {
	m_cityRenderer.render(m_city, m_player.getLocation());
}
