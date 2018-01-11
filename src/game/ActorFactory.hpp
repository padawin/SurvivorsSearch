#ifndef __ACTOR_FACTORY__
#define __ACTOR_FACTORY__

#include "Actor.hpp"
#include "../behaviour/Factory.hpp"

class ActorFactory {
	private:
	static void _setAttributes(std::shared_ptr<GameActor> actor);

	public:
	static std::shared_ptr<GameActor> createActor(E_ActorRace race, E_ActorType type);
	static void setBehaviour(BehaviourFactory &behaviourFactory, std::shared_ptr<Actor> actor);
};

#endif
