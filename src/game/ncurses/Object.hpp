#ifndef __NCURSES_OBJECT__
#define __NCURSES_OBJECT__

#include "../../renderer/Object.hpp"

class NCursesObject : public ObjectRenderer {
	public:
	void render(std::shared_ptr<Object> object, FieldOfView &fov, int displayShiftX, int displayShiftY);
};

#endif
