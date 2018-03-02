#include "Dialogue.hpp"
#include "../../Actor.hpp"
#include "../types.hpp"

DialogueWindow::DialogueWindow(Dialogue &dialogues) : m_dialogues(dialogues) {
}

void DialogueWindow::setDialogue(std::string dialogue) {
	m_sDialogue = dialogue;
}

void DialogueWindow::onNotify(E_Event event, Actor *actor __attribute__((unused))) {
	if (event == SURVIVOR_SAVED) {
		setDialogue(m_dialogues.getDialogue("SURVIVOR_SAVED"));
	}
}

void DialogueWindow::render() {

}
