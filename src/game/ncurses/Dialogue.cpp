#include "Dialogue.hpp"
#include "../../utils.hpp"
#include "../../Actor.hpp"
#include "../types.hpp"

DialogueWindow::DialogueWindow(UserActions &userActions, Dialogue &dialogues) :
	m_dialogues(dialogues),
	m_userActions(userActions)
{
}

bool DialogueWindow::hasDialogue() {
	return m_vDialogue.size() > 0;
}

void DialogueWindow::setDialogue(std::string dialogue) {
	unsigned long start = 0,
				  end = 0;
	unsigned int maxWidth = (unsigned) (m_area.width - 2);
	// splits the dialogue into lines fitting into the window
	while (end < dialogue.size()) {
		start = end;
		size_t nextCR = dialogue.find('\n', (size_t) start + 1);
		if (nextCR - start < maxWidth) {
			end = nextCR;
		}
		else {
			end += maxWidth;
			while (
					end < dialogue.size()
					&& end > start
					&& dialogue[end] != ' ' && dialogue[end] != '\n'
				  ) {
				end--;
			}

			if (end == start) {
				end += maxWidth;
			}
		}
		std::string line = dialogue.substr(start, end - start);
		trim(line);
		m_vDialogue.push_back(line);
	}
}

void DialogueWindow::onNotify(E_Event event, Actor *actor __attribute__((unused))) {
	if (event == SURVIVOR_SAVED) {
		setDialogue(m_dialogues.getDialogue("SURVIVOR_SAVED"));
	}
}

void DialogueWindow::update() {
	if (m_userActions.getActionState("NEXT_DIALOGUE_PAGE")) {
		// remove the first lines of m_vDialogue
		m_vDialogue.erase(
			m_vDialogue.begin(),
			m_vDialogue.begin() + m_area.height - 2
		);
	}
}

void DialogueWindow::render() {
	for (
		int line = 0;
		(unsigned) line < m_vDialogue.size() && line < m_area.height - 2;
		++line
	) {
		renderString(
			1,
			line + 1,
			m_vDialogue[(unsigned) line].c_str()
		);
	}
	NCurseWindow::render();
}