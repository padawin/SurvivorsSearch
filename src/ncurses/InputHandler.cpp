#include "InputHandler.hpp"
#include <ncurses.h>

InputUpdateResult NCursesInputHandler::_processEvents() {
	m_mKeysStates.clear();
	int ch;
	InputUpdateResult res = HAS_NO_EVENT;
	while ((ch = getch()) != -1) {
		if (ch == 27) {
			res = QUIT;
			break;
		}

		_handleKeyEvent(ch, true);
		res = HAS_EVENT;
	}
	return res;
}
