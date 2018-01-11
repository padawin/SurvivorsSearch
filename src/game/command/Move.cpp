#include "Move.hpp"
#include "../Actor.hpp"
#include "../../Map.hpp"

bool MoveCommand::execute(Map &map, int xDest, int yDest, Actor* actor) {
	return map.moveActor(actor, xDest, yDest);
}
