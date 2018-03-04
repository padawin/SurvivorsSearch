#ifndef __DIALOGUE_PARSER__
#define __DIALOGUE_PARSER__

#include "FileParser.hpp"
#include "Dialogue.hpp"

class DialogueParser : public FileParser {
	private:
	Dialogue &m_dialogue;
	std::string m_sCurrentId = "";

	bool _parseLine(const char *line);

	public:
	DialogueParser(Dialogue &dialogue);
};

#endif
