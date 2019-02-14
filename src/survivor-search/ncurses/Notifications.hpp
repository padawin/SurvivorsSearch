#ifndef __NOTIFICATION_WINDOW__
#define __NOTIFICATION_WINDOW__

#include "../game/Observer.hpp"
#include "../game/Queue.hpp"
#include "Window.hpp"

class NotificationWindow : public NCurseWindow, public Observer {
	private:
	Queue m_qMessages;

	public:
	NotificationWindow();
	~NotificationWindow();
	void onNotify(E_Event event, Actor *actor = 0);
	void render();
};

#endif
