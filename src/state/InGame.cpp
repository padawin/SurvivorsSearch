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
	m_city.addActor(&m_player);
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
	m_cityRenderer.render(m_city, m_player.getLocation());
}
