#include "../../FieldOfView.hpp"
#include "../../StateMachine.hpp"
#include "../Save.hpp"
#include "../ncurses/Actor.hpp"
#include "../ActorFactory.hpp"
#include "InGame.hpp"

InGame::InGame(UserActions &userActions) :
	State(userActions),
	m_player(ActorFactory::createActor(HUMAN, PLAYER)),
	m_city(City()),
	m_gameView(NCurseWindow()),
	m_messagesView(NCurseWindow()),
	m_cityRenderer(NCursesMap(m_gameView)),
	m_actorRenderer(NCursesActor(m_gameView)),
	m_behaviourFactory(BehaviourFactory(userActions, m_player)),
	m_notifications(Notifications())
{
	m_camera.x = 0;
	m_camera.y = 0;
	m_camera.width = 74;
	m_camera.height = 29;
	m_messagesRect.x = m_camera.width;
	m_messagesRect.y = 0;
	m_messagesRect.width = 35;
	m_messagesRect.height = m_camera.height;

	m_city.init();
	m_behaviourFactory.getBehaviour(BEHAVIOUR_PLAYER)->addObserver(&m_notifications);
	m_behaviourFactory.getBehaviour(BEHAVIOUR_ZOMBIE)->addObserver(&m_notifications);
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
	m_gameView.init(m_camera);
	m_messagesView.init(m_messagesRect);

	_renderGame();
	_renderMessages();

	m_gameView.render();
	m_messagesView.render();
}

void InGame::_renderGame() {
	S_Rectangle visibleArea;
	visibleArea.x = m_player->getLocation().x - m_camera.width / 2;
	visibleArea.y = m_player->getLocation().y - m_camera.height / 2;
	visibleArea.width = m_camera.width - 2;
	visibleArea.height = m_camera.height - 2;
	FieldOfView fov(visibleArea);
	fov.calculate(m_city, m_player->getLocation());
	int shiftX = 1 + m_camera.x - visibleArea.x;
	int shiftY = 1 + m_camera.y - visibleArea.y;
	m_cityRenderer.render(m_city, fov, shiftX, shiftY);
	for (auto actor : m_city.getActors()) {
		m_actorRenderer.render(actor.second, fov, shiftX, shiftY);
	}
}

void InGame::_renderMessages() {
	Queue &messages = m_notifications.getMessages();
	S_QueueItem *message;
	int y = 1;
	while ((message = messages.next())) {
		m_messagesView.renderString(1, y, message->value);
		++y;
	}
}
