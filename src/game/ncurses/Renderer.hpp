#ifndef __NCURSES_RENDERER__
#define __NCURSES_RENDERER__

#include "../../renderer/Renderer.hpp"

class NCursesRenderer : public Renderer {
	public:
	bool init(void) const;
	void frame(Game* game) const;
	void shutdown(void) const;
	static void _closeNCurses(int code);
};

#endif
