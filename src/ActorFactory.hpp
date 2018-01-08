#ifndef __ACTOR_FACTORY__
#define __ACTOR_FACTORY__

#include "Actor.hpp"

class ActorFactory {
	private:
	static void _setAttributes(std::shared_ptr<Actor> actor);

	public:
	static std::shared_ptr<Actor> createActor(E_ActorRace race, E_ActorType type);
};

#endif
