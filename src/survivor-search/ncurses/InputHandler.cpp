#include "InputHandler.hpp"
#include <ncurses.h>

void NCursesInputHandler::_processEvents() {
	m_mKeysStates.clear();
	int ch;
	while ((ch = getch()) != -1) {
		_handleKeyEvent(ch, true);
	}
}
