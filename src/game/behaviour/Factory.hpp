#ifndef __BEHAVIOUR__FACTORY__
#define __BEHAVIOUR__FACTORY__

#include <vector>
#include <memory>
#include "../UserActions.hpp"
#include "../Actor.hpp"

class Behaviour;

class BehaviourFactory {
	private:
	std::vector<std::shared_ptr<Behaviour>> m_vBehaviours = {};

	public:
	BehaviourFactory(UserActions &userActions, std::shared_ptr<Actor> player);
	std::shared_ptr<Behaviour> getBehaviour(E_Behaviours behaviour) {
		return m_vBehaviours[behaviour];
	}
};

#endif
