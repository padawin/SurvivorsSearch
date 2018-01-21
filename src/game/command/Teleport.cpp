#include "Teleport.hpp"
#include "../../Map.hpp"
#include "../Actor.hpp"

bool TeleportCommand::execute(Map &map, int xDest, int yDest, Actor* actor __attribute__((unused))) {
	//shoot teleport projectile to xDest, yDest, set speed to dest - actor
	std::shared_ptr<Actor> target = map.getActorAt(xDest, yDest);
	if (target == NULL || target->getType() != SURVIVOR) {
		return false;
	}

	map.removeActor(xDest, yDest);
	map.update();
	return true;
}
