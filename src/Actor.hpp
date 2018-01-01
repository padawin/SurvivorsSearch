#ifndef __ACTOR__
#define __ACTOR__

#include <memory>
#include "types.hpp"

class Map;

enum E_ActorOrientation {LEFT, RIGHT};

class Actor {
	friend class Save;
	private:
	char m_sCity[20];
	int m_iHealth = 0;
	int m_iMaxHealth = 0;
	int m_iDefence = 0;
	int m_iAttack = 0;

	S_Coordinates m_location = S_Coordinates();

	public:
	int getHealth();
	int getMaxHealth();
	int getDefence();
	int getAttack();
	void setHealth(int health);
	void setMaxHealth(int maxHealth);
	void setDefence(int defence);
	void setAttack(int attack);

	bool isDead();

	void setX(int x);
	void setY(int y);
	char* getCity();
	S_Coordinates getLocation();

	void render(int displayShiftX, int displayShiftY);

	bool isNextTo(std::shared_ptr<Actor> actor);
	bool seesActor(/*Map &map, */std::shared_ptr<Actor> actor);

	void attack(std::shared_ptr<Actor> target);
};

#endif
