#ifndef __MESSAGES_VIEW__
#define __MESSAGES_VIEW__

#include <string>
#include "../Observer.hpp"
#include "../Queue.hpp"

class Notifications : public Observer {
	private:
	Queue m_qMessages;

	public:
	Notifications();
	~Notifications();
	void onNotify(E_Event event, Actor &actor);
};

#endif
