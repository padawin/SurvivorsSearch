#include "InGame.hpp"
#include "../StateMachine.hpp"
#include "../Save.hpp"
#include "../ncurses/Actor.hpp"

InGame::InGame(UserActions &userActions) :
	State(userActions),
	m_player(Actor()),
	m_city(City()),
	m_cityRenderer(NCursesMap())
{
	m_city.init();
	std::shared_ptr<ActorRenderer> renderer(new NCursesActor('@'));
	m_player.setRenderer(renderer);
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

void InGame::update() {
	S_Coordinates location = m_player.getLocation();

	if (m_userActions.getActionState("MOVE_PLAYER_UP")) {
		m_city.moveActor(&m_player, location.x, location.y - 1);
	}
	else if (m_userActions.getActionState("MOVE_PLAYER_DOWN")) {
		m_city.moveActor(&m_player, location.x, location.y + 1);
	}
	else if (m_userActions.getActionState("MOVE_PLAYER_LEFT")) {
		m_city.moveActor(&m_player, location.x - 1, location.y);
	}
	else if (m_userActions.getActionState("MOVE_PLAYER_RIGHT")) {
		m_city.moveActor(&m_player, location.x + 1, location.y);
	}
}

void InGame::render() {
	m_cityRenderer.render(m_city, m_player.getLocation());
}
