#ifndef __TELEPORT_COMMAND__
#define __TELEPORT_COMMAND__

#include "Command.hpp"

class Actor;
class Map;

class TeleportCommand : public Command {
	public:
	bool execute(Map &map, int xDest, int yDest, Actor* actor=0);
};

#endif
