#ifndef __NCURSES_RENDERER__
#define __NCURSES_RENDERER__

#include "../game/renderer/Renderer.hpp"

class NCursesRenderer : public Renderer {
	public:
	bool init(void);
	void frame(Game* game) const;
	void shutdown(void);
	static void _closeNCurses(int code);
};

#endif
