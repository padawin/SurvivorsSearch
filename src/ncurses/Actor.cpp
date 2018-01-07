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
	else {
		switch (actor->getRace()) {
			case ZOMBIE:
				c = 'z';
				break;
			case HUMAN:
				c = 'H';
				break;
			default:
				c = '?';
				break;
		}
	}
	mvaddch(displayShiftY + y, displayShiftX + x, c);
}
