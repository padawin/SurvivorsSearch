#ifndef __BEHAVIOUR__
#define __BEHAVIOUR__

#include "../Observable.hpp"

class Actor;
class Map;

class Behaviour : public Observable {
	public:
	virtual bool update(Actor *actor, Map &map) = 0;
	virtual ~Behaviour() {};
};

#endif
