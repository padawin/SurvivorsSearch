#include "Move.hpp"
#include "../Map.hpp"
#include "../Actor.hpp"

bool MoveCommand::execute(Map &map, int xDest, int yDest, Actor* actor) {
	return map.moveActor(actor, xDest, yDest);
}
