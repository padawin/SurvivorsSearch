#include "Attack.hpp"
#include "../Map.hpp"
#include "../Actor.hpp"
#include <cstdarg>

bool AttackCommand::execute(Map &map, int xDest, int yDest, Actor *actor) {
	std::shared_ptr<Actor> target = map.getActorAt(xDest, yDest);
	if (target == NULL) {
		return false;
	}

	actor->attack(target);
	return true;
}
