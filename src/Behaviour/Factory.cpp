#include "Factory.hpp"
#include "Player.hpp"

BehaviourFactory::BehaviourFactory(UserActions &userActions) {
	std::shared_ptr<BehaviourPlayer> p(new BehaviourPlayer(userActions));
	m_vBehaviours = {
		p
	};
}

std::shared_ptr<Behaviour> BehaviourFactory::getBehaviour(E_Behaviours behaviour) {
	return m_vBehaviours[behaviour];
}
