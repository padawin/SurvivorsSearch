#include "Dialogue.hpp"

void Dialogue::_addLine(std::string id, std::string line) {
	if (m_mDialogues.find(id) == m_mDialogues.end()) {
		m_mDialogues[id] = line;
	}
	else {
		m_mDialogues[id] += "\n";
		m_mDialogues[id] += line;
	}
}
