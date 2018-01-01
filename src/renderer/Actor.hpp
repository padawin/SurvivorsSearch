#ifndef __ACTOR_RENDERER__
#define __ACTOR_RENDERER__

class Actor;
class ActorRenderer {
	public:
	virtual ~ActorRenderer() {}
	virtual void render(Actor &actor, int displayShiftX, int displayShiftY) = 0;
};

#endif
