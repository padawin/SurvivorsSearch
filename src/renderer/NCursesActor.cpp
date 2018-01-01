#include "NCursesActor.hpp"
#include "../Actor.hpp"
#include <ncurses.h>

NCursesActor::NCursesActor(char c) : m_cCharacter(static_cast<unsigned char>(c)) {
}

void NCursesActor::render(Actor &actor, int displayShiftX, int displayShiftY) {
	mvaddch(
		displayShiftY + actor.getLocation().y,
		displayShiftX + actor.getLocation().x,
		m_cCharacter
	);
}
