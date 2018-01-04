#ifndef __ACTOR_RENDERER__
#define __ACTOR_RENDERER__

#include <memory>

class Actor;
class ActorRenderer {
	public:
	virtual ~ActorRenderer() {}
	virtual void render(std::shared_ptr<Actor> actor, int displayShiftX, int displayShiftY) = 0;
};

#endif
