#include "ActorFactory.hpp"

std::shared_ptr<Actor> ActorFactory::createActor(E_ActorRace race, E_ActorType type) {
	std::shared_ptr<Actor> actor(new Actor(race, type));
	_setAttributes(actor);
	return actor;
}

void ActorFactory::_setAttributes(std::shared_ptr<Actor> actor) {
	switch (actor->getRace()) {
		case HUMAN:
			actor->setHealth(3);
			actor->setMaxHealth(3);
			actor->setAttack(1);
			break;
		case ZOMBIE:
			actor->setHealth(2);
			actor->setMaxHealth(2);
			actor->setAttack(1);
			break;
		default:
			break;
	}
}
