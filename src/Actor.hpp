#ifndef __ACTOR__
#define __ACTOR__

#include "types.hpp"
#include "renderer/Actor.hpp"
#include "behaviour/Behaviour.hpp"
#include "Map.hpp"
#include <memory>

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

	std::shared_ptr<ActorRenderer> m_renderer = 0;
	std::shared_ptr<Behaviour> m_behaviour = 0;

	public:
	~Actor() {}
	void setRenderer(std::shared_ptr<ActorRenderer> renderer);
	void setBehaviour(std::shared_ptr<Behaviour> behaviour);

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

	bool update(Map &map);
	void render(int displayShiftX, int displayShiftY);

	bool isNextTo(std::shared_ptr<Actor> actor);
	bool seesActor(Map &map, std::shared_ptr<Actor> actor);

	void attack(std::shared_ptr<Actor> target);
};

#endif
