#include "Actor.hpp"
#include "../Actor.hpp"
#include <ncurses.h>

void NCursesActor::render(std::shared_ptr<Actor> actor, int displayShiftX, int displayShiftY) {
	mvaddch(
		displayShiftY + actor->getLocation().y,
		displayShiftX + actor->getLocation().x,
		'@'
	);
}
