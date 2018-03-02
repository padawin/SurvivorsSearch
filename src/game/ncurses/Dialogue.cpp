#include "Dialogue.hpp"
#include "../../Actor.hpp"

void DialogueWindow::setDialogue(std::string dialogue) {
	m_sDialogue = dialogue;
}

void DialogueWindow::onNotify(E_Event event, Actor *actor __attribute__((unused))) {
	printf("Dialogue notified: %d", event);
}

void DialogueWindow::render() {

}
