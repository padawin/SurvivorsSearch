#include "Notifications.hpp"
#include "../Actor.hpp"
#include "../types.hpp"

const short MAX_NB_MESSAGES = 20;

NotificationWindow::NotificationWindow() : m_qMessages(Queue()) {}

NotificationWindow::~NotificationWindow() {
	m_qMessages.clear();
}

void NotificationWindow::onNotify(E_Event event, Actor *actor) {
	char message[64] = "\0";
	std::string name = "Someone";
	if (actor != 0) {
		name = actor->getName();
	}

	if (event == PLAYER_ATTACKED) {
		sprintf(message, "%s hits you.", name.c_str());
	}
	else if (event == PLAYER_ATTACK) {
		sprintf(message, "You hit %s.", name.c_str());
	}
	else if (event == SURVIVOR_SAVED) {
		sprintf(message, "You saved a survivor.");
	}

	if (m_qMessages.getSize() == MAX_NB_MESSAGES) {
		m_qMessages.pop();
	}

	if (message[0] != '\0') {
		m_qMessages.push(message);
	}
}

void NotificationWindow::render() {
	S_QueueItem *message;
	int y = 1;
	while ((message = m_qMessages.next())) {
		renderString(1, y, message->value);
		++y;
	}
	NCurseWindow::render();
}
