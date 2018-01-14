#ifndef __OBSERVER__
#define __OBSERVER__

#include "types.hpp"

class Actor;
class Observer {
	public:
	virtual ~Observer() {}
	virtual void onNotify(E_Event event, Actor &actor) = 0;
};

#endif
