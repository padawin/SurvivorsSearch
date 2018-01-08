#ifndef __ACTOR_FACTORY__
#define __ACTOR_FACTORY__

#include "Actor.hpp"

class ActorFactory {
	public:
	static std::shared_ptr<Actor> createActor(E_ActorRace race, E_ActorType type);
};

#endif
