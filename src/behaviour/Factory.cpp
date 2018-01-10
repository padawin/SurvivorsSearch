#include "Factory.hpp"
#include "Player.hpp"
#include "Zombie.hpp"

BehaviourFactory::BehaviourFactory(UserActions &userActions, std::shared_ptr<Actor> player) {
	std::shared_ptr<BehaviourPlayer> p(new BehaviourPlayer(userActions));
	std::shared_ptr<BehaviourZombie> m(new BehaviourZombie(player));
	m_vBehaviours = {p, m};
}

std::shared_ptr<Behaviour> BehaviourFactory::getBehaviour(E_Behaviours behaviour) {
	return m_vBehaviours[behaviour];
}
