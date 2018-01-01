#ifndef __GAME_STATE__
#define __GAME_STATE__

#include "../State.hpp"
#include "../types.hpp"
#include <ncurses.h>
#include "../Player.hpp"
#include "../City.hpp"

class InGame : public State {
	private:
	int m_iX = 0;
	int m_iY = 0;
	int m_iWinX = 0;
	int m_iWinY = 0;

	Player m_player;
	City m_city;
	S_Rectangle m_viewCity = {};

	const char* _getCellDisplayValue(int x, int y);

	public:
	InGame();
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
