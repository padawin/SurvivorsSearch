#ifndef __NCURSES_MAP__
#define __NCURSES_MAP__

#include "Map.hpp"
#include "../types.hpp"

class NCursesMap : public MapRenderer {
	private:
	const char* _getCellDisplayValue(Map &map, int x, int y);
	S_Rectangle m_view = {};

	public:
	NCursesMap();
	void render(Map &map, MapContent &content, S_Coordinates reference);
};

#endif
