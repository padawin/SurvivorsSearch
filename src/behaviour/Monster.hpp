#ifndef __BEHAVIOUR_MONSTER__
#define __BEHAVIOUR_MONSTER__

#include "Behaviour.hpp"

class rRpg;
class Actor;

class BehaviourMonster : public Behaviour {
	private:
	Actor &m_player;
	void _executeMove(Actor *actor, Map &map, const int x, const int y);
	void _executeRandomMove(Actor *actor, Map &map);

	public:
	BehaviourMonster(Actor &player);
	bool update(Actor *actor, Map &map);
};

#endif
