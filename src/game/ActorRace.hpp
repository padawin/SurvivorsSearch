#ifndef __ACTOR_RACE__
#define __ACTOR_RACE__

#include "commonTypes.hpp"
#include <memory>

class Actor;

class ActorRace {
	private:
	S_ActorRaceData m_data;

	public:
	ActorRace(S_ActorRaceData data);
	std::shared_ptr<Actor> createActor(E_ActorType actorType);
};

#endif
