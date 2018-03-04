#include "DialogueParser.hpp"
#include <string.h>

DialogueParser::DialogueParser(Dialogue &dialogue) : m_dialogue(dialogue) {}

bool DialogueParser::_parseLine(const char *line) {
	if (strncmp(line, "---", 3) == 0) {
		m_sCurrentId = "";
	}
	else if (m_sCurrentId == "") {
		m_sCurrentId = line;
	}
	else {
		m_dialogue._addLine(m_sCurrentId, line);
	}
	return true;
}
