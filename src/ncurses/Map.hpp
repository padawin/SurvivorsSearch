#ifndef __NCURSES_MAP__
#define __NCURSES_MAP__

#include "../game/renderer/Map.hpp"
#include "../game/types.hpp"
#include "Window.hpp"

class NCursesMap : public MapRenderer {
	private:
	const char* _getCellDisplayValue(Map &map, int visible, int x, int y);
	NCurseWindow &m_window;

	public:
	NCursesMap(NCurseWindow &window);
	void render(Map &map, FieldOfView &fov, int shiftX, int shiftY);
};

#endif
