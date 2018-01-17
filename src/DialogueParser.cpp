#include "DialogueParser.hpp"
#include <string.h>

DialogueParser::DialogueParser(Dialogue &dialogue) : m_dialogue(dialogue) {}

bool DialogueParser::_parseLine(const char *line) {
	if (m_sCurrentId == "") {
		m_sCurrentId = line;
	}
	else if (strncmp(line, "---", 3) == 0) {
		m_dialogue._addLine(m_sCurrentId, line);
	}
	else {
		m_sCurrentId = "";
	}
	return true;
}
