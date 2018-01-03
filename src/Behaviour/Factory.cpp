#include "Factory.hpp"
#include "Player.hpp"

BehaviourFactory::BehaviourFactory() {
	m_vBehaviours = {
		std::make_shared<BehaviourPlayer>()
	};
}

std::shared_ptr<Behaviour> BehaviourFactory::getBehaviour(E_Behaviours behaviour) {
	return m_vBehaviours[behaviour];
}
