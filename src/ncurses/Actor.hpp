#ifndef __NCURSES_ACTOR__
#define __NCURSES_ACTOR__

#include "../renderer/Actor.hpp"

class NCursesActor : public ActorRenderer {
	public:
	void render(std::shared_ptr<Actor> actor, int displayShiftX, int displayShiftY);
};

#endif
