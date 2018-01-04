#include "Factory.hpp"
#include "Player.hpp"
#include "Monster.hpp"

BehaviourFactory::BehaviourFactory(UserActions &userActions, std::shared_ptr<Actor> player) {
	std::shared_ptr<BehaviourPlayer> p(new BehaviourPlayer(userActions));
	std::shared_ptr<BehaviourMonster> m(new BehaviourMonster(player));
	m_vBehaviours = {p, m};
}

std::shared_ptr<Behaviour> BehaviourFactory::getBehaviour(E_Behaviours behaviour) {
	return m_vBehaviours[behaviour];
}
