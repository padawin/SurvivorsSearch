#ifndef __NCURSES_MAP__
#define __NCURSES_MAP__

#include "../../renderer/Map.hpp"
#include "../types.hpp"

class NCursesMap : public MapRenderer {
	private:
	const char* _getCellDisplayValue(Map &map, int visible, int x, int y);

	public:
	void render(Map &map, FieldOfView &fov, int shiftX, int shiftY);
};

#endif
