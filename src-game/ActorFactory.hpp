#ifndef __ACTOR_FACTORY__
#define __ACTOR_FACTORY__

#include <unordered_map>
#include "Actor.hpp"
#include "dataTypes.hpp"
#include "ActorRace.hpp"
#include "behaviour/Factory.hpp"

class ActorFactory {
	private:
	std::unordered_map<E_ActorRace, ActorRace> m_mTaxonomy = {};

	static void _setAttributes(std::shared_ptr<Actor> actor);

	public:
	ActorFactory();
	bool parseTaxonomy(const char* taxonomyFile);
	std::shared_ptr<Actor> createActor(E_ActorRace race, E_ActorType type);
};

#endif
