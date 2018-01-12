#ifndef __MESSAGES_VIEW__
#define __MESSAGES_VIEW__

#include <string>
#include <vector>
#include "../Observer.hpp"

class Notifications : public Observer {
	private:
	std::vector<std::string> m_vMessages = {};

	public:
	void onNotify(E_Event event, Actor &actor);
};

#endif
