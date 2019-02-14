#include "Actor.hpp"
#include <limits.h>
#include <math.h>

#define LIMIT_FIELD_OF_VIEW 6

void GameActor::setHealth(int health) { m_iHealth = health; }
void GameActor::setMaxHealth(int maxHealth) { m_iMaxHealth = maxHealth; }
void GameActor::setAttack(int attackValue) { m_iAttack = attackValue; }
int GameActor::getHealth() { return m_iHealth; }
int GameActor::getMaxHealth() { return m_iMaxHealth; }
int GameActor::getAttack() { return m_iAttack; }

bool GameActor::isDead() {
	return m_iHealth == 0;
}

void GameActor::attack(std::shared_ptr<GameActor> target) {
	int attackValue = rand() % (m_iAttack + 1);
	// no branching max(0, damages)
	target->m_iHealth -= attackValue & -(0 < attackValue);
	// if the health is < 0 cap it at 0
	target->m_iHealth = target->m_iHealth & -(0 < target->m_iHealth);
}
