#ifndef __BEHAVIOUR_ZOMBIE__
#define __BEHAVIOUR_ZOMBIE__

#include "Behaviour.hpp"
#include <memory>

class rRpg;
class Actor;

class BehaviourZombie : public Behaviour {
	private:
	std::shared_ptr<Actor> m_player;
	void _executeMove(Actor *actor, Map &map, const int x, const int y);
	void _executeRandomMove(Actor *actor, Map &map);

	public:
	BehaviourZombie(std::shared_ptr<Actor> player);
	bool update(Actor *actor, Map &map);
};

#endif
