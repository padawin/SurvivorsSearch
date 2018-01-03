#ifndef __BEHAVIOUR__FACTORY__
#define __BEHAVIOUR__FACTORY__

#include <vector>
#include <memory>

class Behaviour;

enum E_Behaviours {BEHAVIOUR_PLAYER, BEHAVIOUR_MONSTER};

class BehaviourFactory {
	private:
	std::vector<std::shared_ptr<Behaviour>> m_vBehaviours = {};

	public:
	BehaviourFactory();
	std::shared_ptr<Behaviour> getBehaviour(E_Behaviours behaviour);

};

#endif
