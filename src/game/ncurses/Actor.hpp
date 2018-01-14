#ifndef __NCURSES_ACTOR__
#define __NCURSES_ACTOR__

#include "../../renderer/Actor.hpp"
#include "Window.hpp"

class NCursesActor : public ActorRenderer {
	private:
	NCurseWindow &m_window;

	public:
	NCursesActor(NCurseWindow &window);
	void render(std::shared_ptr<Actor> actor, FieldOfView &fov, int displayShiftX, int displayShiftY);
};

#endif
