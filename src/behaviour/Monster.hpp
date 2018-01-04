#ifndef __BEHAVIOUR_MONSTER__
#define __BEHAVIOUR_MONSTER__

#include "Behaviour.hpp"
#include <memory>

class rRpg;
class Actor;

class BehaviourMonster : public Behaviour {
	private:
	std::shared_ptr<Actor> m_player;
	void _executeMove(Actor *actor, Map &map, const int x, const int y);
	void _executeRandomMove(Actor *actor, Map &map);

	public:
	BehaviourMonster(std::shared_ptr<Actor> player);
	bool update(Actor *actor, Map &map);
};

#endif
