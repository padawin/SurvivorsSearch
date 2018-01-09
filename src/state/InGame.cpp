#include "InGame.hpp"
#include "../FieldOfView.hpp"
#include "../StateMachine.hpp"
#include "../Save.hpp"
#include "../ncurses/Actor.hpp"
#include "../behaviour/Factory.hpp"
#include "../ActorFactory.hpp"

InGame::InGame(UserActions &userActions) :
	State(userActions),
	m_player(ActorFactory::createActor(HUMAN, PLAYER)),
	m_city(City()),
	m_cityRenderer(NCursesMap()),
	m_actorRenderer(NCursesActor()),
	m_behaviourFactory(BehaviourFactory(userActions, m_player))
{
	m_camera.x = 0;
	m_camera.y = 0;
	m_camera.width = 79;
	m_camera.height = 29;
	m_city.init();
}

std::string InGame::getStateID() const {
	return "TestState";
}

bool InGame::onEnter() {
	if (!Save::exists()) {
		Save::clean();
		Save::create(m_player, m_city);
	}
	else {
		Save::load(m_player, m_city);
	}

	m_city.addActor(m_player);
	for (auto actor : m_city.getActors()) {
		ActorFactory::setBehaviour(m_behaviourFactory, actor.second);
	}
	return true;
}

void InGame::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}

	if (!m_player->update(m_city)) {
		return;
	}

	for (auto actor : m_city.getActors()) {
		if (actor.second != m_player) {
			actor.second->update(m_city);
		}
	}

	if (m_player->isDead()) {
		stateMachine.clean();
	}
}

void InGame::render() {
	S_Rectangle visibleArea = m_camera;
	visibleArea.x = m_player->getLocation().x - m_camera.width / 2;
	visibleArea.y = m_player->getLocation().y - m_camera.height / 2;
	FieldOfView fov(visibleArea);
	fov.calculate(m_city, m_player->getLocation());
	int shiftX = m_camera.x - visibleArea.x;
	int shiftY = m_camera.y - visibleArea.y;
	m_cityRenderer.render(m_city, fov, shiftX, shiftY);
	for (auto actor : m_city.getActors()) {
		m_actorRenderer.render(actor.second, fov, shiftX, shiftY);
	}
}
