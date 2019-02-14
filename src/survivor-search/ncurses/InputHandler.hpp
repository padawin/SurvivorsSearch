#ifndef __NCURSES_INPUT_HANDLER__
#define __NCURSES_INPUT_HANDLER__

#include "../game/InputHandler.hpp"

class NCursesInputHandler : public InputHandler {
	protected:
	void _processEvents();
};

#endif
