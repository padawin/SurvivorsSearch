#include "Attack.hpp"
#include "../../Map.hpp"
#include "../Actor.hpp"
#include <cstdarg>

bool AttackCommand::execute(Map &map, int xDest, int yDest, Actor *actor) {
	// std::shared_ptr<GameActor> target = map.getActorAt(xDest, yDest);
	std::shared_ptr<GameActor> target = std::static_pointer_cast<GameActor>(map.getActorAt(xDest, yDest));
	GameActor *a = static_cast<GameActor *>(actor);
	if (target == NULL) {
		return false;
	}

	a->attack(target);
	if (target->isDead()) {
		map.removeActor(xDest, yDest);
	}
	return true;
}
