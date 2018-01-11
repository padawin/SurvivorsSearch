#include "ActorFactory.hpp"

std::shared_ptr<GameActor> ActorFactory::createActor(E_ActorRace race, E_ActorType type) {
	std::shared_ptr<GameActor> actor(new GameActor(race, type));
	_setAttributes(actor);
	return actor;
}

void ActorFactory::setBehaviour(BehaviourFactory &behaviourFactory, std::shared_ptr<Actor> actor) {
	if (actor->getType() == PLAYER) {
		actor->setBehaviour(behaviourFactory.getBehaviour(BEHAVIOUR_PLAYER));
	}
	else if (actor->getType() == FOE) {
		actor->setBehaviour(behaviourFactory.getBehaviour(BEHAVIOUR_ZOMBIE));
	}
}

void ActorFactory::_setAttributes(std::shared_ptr<GameActor> actor) {
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
		case LARGE_ZOMBIE:
			actor->setHealth(3);
			actor->setMaxHealth(3);
			actor->setAttack(2);
			break;
		default:
			break;
	}
}
