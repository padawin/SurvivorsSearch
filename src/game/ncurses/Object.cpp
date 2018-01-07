#include "Object.hpp"
#include "../../Object.hpp"
#include <ncurses.h>

void NCursesObject::render(std::shared_ptr<Object> object, FieldOfView &fov, int displayShiftX, int displayShiftY) {
	int x = object->getLocation().x,
		y = object->getLocation().y;
	if (!fov.isVisible(x, y)) {
		return;
	}
	unsigned char c = ' ';
	if (object->getType() == PROJECTILE) {
		c = '*';
	}
	mvaddch(displayShiftY + y, displayShiftX + x, c);
}
