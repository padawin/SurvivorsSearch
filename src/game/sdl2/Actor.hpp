#ifndef __SDL2_ACTOR__
#define __SDL2_ACTOR__

#include "../../renderer/Actor.hpp"

class SDL2Actor : public ActorRenderer {
	public:
	void render(std::shared_ptr<Actor> actor, FieldOfView &fov, int displayShiftX, int displayShiftY);
};

#endif
