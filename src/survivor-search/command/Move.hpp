#ifndef __MOVE_COMMAND__
#define __MOVE_COMMAND__

#include "../game/Command.hpp"

class MoveCommand : public Command {
	public:
	bool execute(Map &map, int xDest, int yDest, Actor* actor=0);
};

#endif
