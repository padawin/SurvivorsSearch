#include "../game/FieldOfView.hpp"
#include "../game/StateMachine.hpp"
#include "../Save.hpp"
#include "../ncurses/Actor.hpp"
#include "../ActorFactory.hpp"
#include "InGame.hpp"

InGame::InGame(UserActions &userActions, Dialogue &dialogues) :
	State(userActions),
	m_player(ActorFactory::createActor(HUMAN, PLAYER)),
	m_city(City()),
	m_gameView(NCurseWindow()),
	m_messagesView(NotificationWindow()),
	m_dialogueView(DialogueWindow(userActions, dialogues)),
	m_cityRenderer(NCursesMap(m_gameView)),
	m_actorRenderer(NCursesActor(m_gameView)),
	m_behaviourFactory(BehaviourFactory(userActions, m_player))
{
	m_camera.x = 0;
	m_camera.y = 0;
	m_camera.width = 74;
	m_camera.height = 25;

	m_city.init();
	m_behaviourFactory.getBehaviour(BEHAVIOUR_PLAYER)->addObserver(&m_messagesView);
	m_behaviourFactory.getBehaviour(BEHAVIOUR_PLAYER)->addObserver(&m_dialogueView);
	m_behaviourFactory.getBehaviour(BEHAVIOUR_ZOMBIE)->addObserver(&m_messagesView);
}

std::string InGame::getStateID() const {
	return "TestState";
}

bool InGame::onEnter() {
	S_Rectangle messagesRect, dialoguesRect;
	messagesRect.x = m_camera.width;
	messagesRect.y = 0;
	messagesRect.width = 35;
	messagesRect.height = m_camera.height + 7;
	dialoguesRect.x = 0;
	dialoguesRect.y = m_camera.y + m_camera.height;
	dialoguesRect.width = m_camera.width;
	dialoguesRect.height = 7;

	m_gameView.init(m_camera);
	m_messagesView.init(messagesRect);
	m_dialogueView.init(dialoguesRect);

	if (!Save::exists()) {
		Save::clean();
		Save::create(m_player, m_city);
		m_dialogueView.onNotify(TUTORIAL, NULL);
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
		Save::save(m_player, m_city);
		stateMachine.clean();
		return;
	}

	if (m_dialogueView.hasDialogue()) {
		m_dialogueView.update();
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
		Save::clean();
		stateMachine.clean();
	}
}

void InGame::render() {
	m_gameView.prepareWindow();
	m_messagesView.prepareWindow();
	m_dialogueView.prepareWindow();

	_renderGame();

	m_gameView.render();
	m_messagesView.render();
	m_dialogueView.render();
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
