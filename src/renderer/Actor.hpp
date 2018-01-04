#ifndef __ACTOR_RENDERER__
#define __ACTOR_RENDERER__

#include <memory>
#include "../FieldOfView.hpp"

class Actor;
class ActorRenderer {
	public:
	virtual ~ActorRenderer() {}
	virtual void render(std::shared_ptr<Actor> actor, FieldOfView &fov, int displayShiftX, int displayShiftY) = 0;
};

#endif
