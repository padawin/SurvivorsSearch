#include "InputHandler.hpp"
#include <ncurses.h>

InputUpdateResult NCursesInputHandler::_processEvents() {
	m_mKeysStates.clear();
	int ch;
	InputUpdateResult ret = HAS_NO_EVENT;
	while ((ch = getch()) != -1) {
		_handleKeyEvent(ch, true);
		ret = HAS_EVENT;
	}

	return ret;
}
