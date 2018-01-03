#ifndef __BEHAVIOUR_PLAYER__
#define __BEHAVIOUR_PLAYER__

#include "Behaviour.hpp"
#include <cstdint>

class Map;
class Actor;
class UserActions;

class BehaviourPlayer : public Behaviour {
	private:
	UserActions *m_userActions = 0;
	bool _isDirectionPressed(int &x, int &y);
	bool _tryMove(Actor *actor, Map &map, int x, int y);
	bool _tryAttack(Actor *actor, Map &map, int x, int y);
	bool _actionDirection(Actor *actor, Map &map);

	public:
	void setUserActions(UserActions *userActions);
	bool update(Actor *actor, Map &map);
};

#endif
