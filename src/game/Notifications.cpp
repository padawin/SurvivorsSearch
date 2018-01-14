#include "Notifications.hpp"
#include "../Actor.hpp"

const short MAX_NB_MESSAGES = 20;

Notifications::Notifications() : m_qMessages(Queue()) {}

Notifications::~Notifications() {
	m_qMessages.clear();
}

void Notifications::onNotify(E_Event event, Actor &actor) {
	char message[64] = "\0";
	if (event == PLAYER_ATTACKED) {
		sprintf(message, "You are hit by %d", actor.getRace());
	}
	else if (event == PLAYER_ATTACK) {
		sprintf(message, "You hit %d", actor.getRace());
	}
	else if (event == SURVIVOR_SAVED) {
		sprintf(message, "You saved a survivor");
	}

	if (m_qMessages.getSize() == MAX_NB_MESSAGES) {
		m_qMessages.pop();
	}

	if (message[0] != '\0') {
		m_qMessages.push(message);
	}
}
