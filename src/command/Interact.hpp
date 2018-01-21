#ifndef __INTERACT_COMMAND__
#define __INTERACT_COMMAND__

#include "../Command.hpp"

class Actor;
class Map;

class InteractCommand : public Command {
	public:
	bool execute(Map &map, int xDest, int yDest, Actor* actor=0);
};

#endif
