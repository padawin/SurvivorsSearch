#ifndef __DIALOGUE__
#define __DIALOGUE__

#include <map>
#include <string>

class Dialogue {
	friend class DialogueParser;

	private:
	std::map<std::string, std::string> m_mDialogues = {};

	void _addLine(std::string id, std::string line);
};

#endif
