#include "Actor.hpp"
#include "../Actor.hpp"
#include <ncurses.h>

void NCursesActor::render(std::shared_ptr<Actor> actor, FieldOfView &fov, int displayShiftX, int displayShiftY) {
	int x = actor->getLocation().x,
		y = actor->getLocation().y;
	if (!fov.isVisible(x, y)) {
		return;
	}
	unsigned char c = ' ';
	if (actor->getType() == PLAYER) {
		c = '@';
	}
	else if (actor->getType() == SURVIVOR) {
		c = 'S';
	}
	mvaddch(displayShiftY + y, displayShiftX + x, c);
}
