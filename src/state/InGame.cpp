#include "InGame.hpp"
#include "../StateMachine.hpp"
#include "../Save.hpp"
#include "../ncurses/Actor.hpp"
#include "../Behaviour/Player.hpp"

InGame::InGame(UserActions &userActions) :
	State(userActions),
	m_player(Actor()),
	m_city(City()),
	m_cityRenderer(NCursesMap()),
	m_behaviourFactory(BehaviourFactory())
{
	m_city.init();
	std::shared_ptr<ActorRenderer> renderer(new NCursesActor('@'));
	m_player.setRenderer(renderer);
	std::shared_ptr<BehaviourPlayer>
		b = std::dynamic_pointer_cast<BehaviourPlayer>(m_behaviourFactory.getBehaviour(BEHAVIOUR_PLAYER));
	b->setUserActions(&m_userActions);
	m_player.setBehaviour(b);
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
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}

	m_player.update(m_city);
	for (auto actor : m_city.getActors()) {
		if (actor.second != &m_player) {
			actor.second->update(m_city);
		}
	}
}

void InGame::render() {
	m_cityRenderer.render(m_city, m_player.getLocation());
}
