#ifndef __NCURSES_WINDOW__
#define __NCURSES_WINDOW__

#include <ncurses.h>
#include "../../types.hpp"

class NCurseWindow {
	protected:
	S_Rectangle m_area = {};
	WINDOW *m_window = 0;

	public:
	~NCurseWindow();
	void init(S_Rectangle area);
	void renderChar(int x, int y, char c);
	void renderString(int x, int y, const char *s);
	void render();
};

#endif
