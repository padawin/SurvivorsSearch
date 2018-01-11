#ifndef __COMMAND__
#define __COMMAND__

class Actor;
class Map;

class Command {
	public:
	virtual ~Command() {};
	virtual bool execute(Map &map, int xDest, int yDest, Actor *actor=0) = 0;
};

#endif
