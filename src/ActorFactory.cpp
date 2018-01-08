#include "ActorFactory.hpp"

std::shared_ptr<Actor> ActorFactory::createActor(E_ActorRace race, E_ActorType type) {
	std::shared_ptr<Actor> actor(new Actor(race, type));
	return actor;
}
