#ifndef __OPEN_COMMAND__
#define __OPEN_COMMAND__

#include "../game/Command.hpp"
#include "../game/Map.hpp"

class OpenCommand : public Command {
	public:
	bool execute(Map &map, int xDest, int yDest, Actor *actor=0);
};

#endif
