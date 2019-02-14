#ifndef __GAME_ACTOR__
#define __GAME_ACTOR__

#include "types.hpp"
#include "../game/Actor.hpp"

class GameActor : public Actor {
	friend class Save;
	private:
	int m_iHealth = 0;
	int m_iMaxHealth = 0;
	int m_iAttack = 0;

	public:
	GameActor(E_ActorRace race, E_ActorType type) : Actor(race, type) {}
	int getHealth();
	int getMaxHealth();
	int getAttack();
	void setHealth(int health);
	void setMaxHealth(int maxHealth);
	void setAttack(int attack);

	bool isDead();

	void attack(std::shared_ptr<GameActor> target);
};

#endif
