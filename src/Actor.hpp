#ifndef __ACTOR__
#define __ACTOR__

#include "types.hpp"
#include "behaviour/Behaviour.hpp"
#include "Map.hpp"
#include <memory>

class Actor {
	friend class Save;
	private:
	int m_iHealth = 0;
	int m_iMaxHealth = 0;
	int m_iAttack = 0;
	E_ActorRace m_eRace;
	E_ActorType m_eType;

	S_Coordinates m_location = S_Coordinates();

	std::shared_ptr<Behaviour> m_behaviour = 0;

	public:
	Actor(E_ActorRace race, E_ActorType type);
	~Actor() {}
	void setBehaviour(std::shared_ptr<Behaviour> behaviour);

	int getHealth();
	int getMaxHealth();
	int getAttack();
	E_ActorType getType();
	E_ActorRace getRace();
	void setHealth(int health);
	void setMaxHealth(int maxHealth);
	void setAttack(int attack);

	bool isDead();

	void setX(int x);
	void setY(int y);
	S_Coordinates getLocation();

	bool update(Map &map);

	bool isNextTo(std::shared_ptr<Actor> actor);
	bool seesActor(Map &map, std::shared_ptr<Actor> actor);

	void attack(std::shared_ptr<Actor> target);
};

#endif
