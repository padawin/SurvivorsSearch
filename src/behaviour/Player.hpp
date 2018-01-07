#ifndef __BEHAVIOUR_PLAYER__
#define __BEHAVIOUR_PLAYER__

#include "Behaviour.hpp"
#include "../UserActions.hpp"
#include <cstdint>

class Map;
class Actor;

class BehaviourPlayer : public Behaviour {
	private:
	UserActions &m_userActions;
	bool _isDirectionPressed(int &x, int &y);
	bool _tryMove(Actor *actor, Map &map, int x, int y);
	bool _tryOpen(Map &map, int x, int y);
	bool _tryInteractActor(Actor *actor, Map &map, int x, int y);
	bool _actionDirection(Actor *actor, Map &map);

	public:
	BehaviourPlayer(UserActions &userActions);
	bool update(Actor *actor, Map &map);
};

#endif
