#include "../game/Map.hpp"
#include "../Actor.hpp"
#include "Move.hpp"

bool MoveCommand::execute(Map &map, int xDest, int yDest, Actor* actor) {
	return map.moveActor(actor, xDest, yDest);
}
