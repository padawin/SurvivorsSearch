#ifndef __NCURSES_ACTOR__
#define __NCURSES_ACTOR__

#include "../renderer/Actor.hpp"

class NCursesActor : public ActorRenderer {
	private:
	unsigned char m_cCharacter = 0;

	public:
	NCursesActor(char c);
	void render(Actor &actor, int displayShiftX, int displayShiftY);
};

#endif
