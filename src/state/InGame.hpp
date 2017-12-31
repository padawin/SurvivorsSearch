#ifndef __GAME_STATE__
#define __GAME_STATE__

#include "../State.hpp"
#include <ncurses.h>

class InGame : public State {
	private:
	int m_iX = 0;
	int m_iY = 0;
	int m_iWinX = 0;
	int m_iWinY = 0;

	public:
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
