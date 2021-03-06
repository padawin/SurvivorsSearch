#include "../game/Actor.hpp"
#include "../survivor-search/types.hpp"
#include "./Actor.hpp"
#include <ncurses.h>

NCursesActor::NCursesActor(NCurseWindow &window) : m_window(window) {
}

void NCursesActor::render(std::shared_ptr<Actor> actor, FieldOfView &fov, int displayShiftX, int displayShiftY) {
	int x = actor->getLocation().x,
		y = actor->getLocation().y;
	if (!fov.isVisible(x, y)) {
		return;
	}
	char c = ' ';
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
			case LARGE_ZOMBIE:
				c = 'Z';
				break;
			case HUMAN:
				c = 'H';
				break;
			default:
				c = '?';
				break;
		}
	}
	m_window.renderChar(displayShiftX + x, displayShiftY + y, c);
}
