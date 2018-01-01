#include "Actor.hpp"
#include <limits.h>
#include <ncurses.h>
#include <math.h>
#include "Map.hpp"

#define LIMIT_FIELD_OF_VIEW 6

void Actor::setHealth(int health) { m_iHealth = health; }
void Actor::setMaxHealth(int maxHealth) { m_iMaxHealth = maxHealth; }
void Actor::setDefence(int defence) { m_iDefence = defence; }
void Actor::setAttack(int attackValue) { m_iAttack = attackValue; }
int Actor::getHealth() { return m_iHealth; }
int Actor::getMaxHealth() { return m_iMaxHealth; }
int Actor::getDefence() { return m_iDefence; }
int Actor::getAttack() { return m_iAttack; }

char* Actor::getCity() { return m_sCity; }

S_Coordinates Actor::getLocation() { return m_location; }

bool Actor::isDead() {
	return m_iHealth == 0;
}

void Actor::setX(int x) { m_location.x = x; }
void Actor::setY(int y) { m_location.y = y; }

void Actor::render(int displayShiftX, int displayShiftY) {
	mvaddstr(
		displayShiftY + m_location.y,
		displayShiftX + m_location.x,
		"@"
	);
}

bool Actor::isNextTo(std::shared_ptr<Actor> actor) {
	int x0 = m_location.x,
		x1 = m_location.y,
		y0 = m_location.y,
		y1 = actor->m_location.y;
	bool isNext = (x0 + 1 == x1) || (x1 + 1 == x0);
	bool isAbove = (y0 + 1 == y1) || (y1 + 1 == y0);
	return (isNext && y0 == y1) || (x0 == x1 && isAbove);
}

bool Actor::seesActor(/*Map &map, */std::shared_ptr<Actor> actor) {
	int x0 = m_location.x,
		y0 = m_location.y,
		x1 = actor->m_location.x,
		y1 = actor->m_location.y;
	int deltaX, deltaY, absDeltaX, absDeltaY;
	bool actor1SeesActor2 = true;
	deltaX = x1 - x0;
	deltaY = y1 - y0;
	absDeltaX = abs(deltaX);
	absDeltaY = abs(deltaY);

	if (absDeltaY > LIMIT_FIELD_OF_VIEW || absDeltaX > LIMIT_FIELD_OF_VIEW) {
		return false;
	}

	return actor1SeesActor2;
}

void Actor::attack(std::shared_ptr<Actor> target) {
	int attackValue = rand() % m_iAttack;
	int defence = rand() % target->m_iDefence;
	int damages = attackValue - defence;
	// no branching max(0, damages)
	target->m_iHealth -= damages & -(0 < damages);
	// if the health is < 0 cap it at 0
	target->m_iHealth = target->m_iHealth & -(0 < target->m_iHealth);
}
