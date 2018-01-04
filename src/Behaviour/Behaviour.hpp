#ifndef __BEHAVIOUR__
#define __BEHAVIOUR__

class Actor;
class Map;

class Behaviour {
	public:
	virtual bool update(Actor *actor, Map &map) = 0;
	virtual ~Behaviour() {};
};

#endif
