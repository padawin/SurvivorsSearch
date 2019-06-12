#include "ActorRace.hpp"
#include "Actor.hpp"

ActorRace::ActorRace(S_ActorRaceData data) :
	m_data(data)
{
}

std::shared_ptr<Actor> ActorRace::createActor(E_ActorType actorType) {
	std::shared_ptr<Actor> actor(std::make_shared<Actor>(*this, actorType));
	actor->setHealth((int) m_data.level1HP);
	actor->setMaxHealth(m_data.level1HP);
	actor->setDefence(m_data.level1Defence);
	actor->setAttack(m_data.level1Attack);
	return actor;
}
