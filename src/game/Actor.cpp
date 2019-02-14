#include "Actor.hpp"
#include <limits.h>
#include <math.h>

#define LIMIT_FIELD_OF_VIEW 6

Actor::Actor(E_ActorRace race, E_ActorType type) :
	m_eRace(race),
	m_eType(type)
{
}

E_ActorType Actor::getType() { return m_eType; }
E_ActorRace Actor::getRace() { return m_eRace; }
std::string Actor::getName() { return m_sName; }

std::string Actor::getScript() { return m_sScript; }

void Actor::setBehaviour(std::shared_ptr<Behaviour> behaviour) { m_behaviour = behaviour; }
void Actor::setName(std::string name) { m_sName = name; }

void Actor::setScript(std::string script) { m_sScript = script; }

S_Coordinates Actor::getLocation() { return m_location; }

void Actor::setX(int x) { m_location.x = x; }
void Actor::setY(int y) { m_location.y = y; }

bool Actor::isDead() {
	return false;
}

bool Actor::update(Map &map) {
	bool updated = true;
	if (m_behaviour != 0) {
		updated = m_behaviour->update(this, map);
	}
	return updated;
}

bool Actor::isNextTo(std::shared_ptr<Actor> actor) {
	int x0 = m_location.x,
		x1 = actor->m_location.x,
		y0 = m_location.y,
		y1 = actor->m_location.y;
	bool isNext = (x0 + 1 == x1) || (x1 + 1 == x0);
	bool isAbove = (y0 + 1 == y1) || (y1 + 1 == y0);
	return (isNext && y0 == y1) || (x0 == x1 && isAbove);
}

bool Actor::seesActor(Map &map, std::shared_ptr<Actor> actor) {
	int x0 = m_location.x,
		y0 = m_location.y,
		x1 = actor->m_location.x,
		y1 = actor->m_location.y,
		x, y,
		directionX, directionY;
	int deltaX, deltaY, absDeltaX, absDeltaY;
	double slope,
		positionOnY0;
	bool actor1SeesActor2 = true;
	deltaX = x1 - x0;
	deltaY = y1 - y0;
	absDeltaX = abs(deltaX);
	absDeltaY = abs(deltaY);

	if (absDeltaY > LIMIT_FIELD_OF_VIEW || absDeltaX > LIMIT_FIELD_OF_VIEW) {
		return false;
	}

	directionX = (x0 < x1) - (x0 > x1);
	directionY = (y0 < y1) - (y0 > y1);

	slope = 0;
	if (x1 != x0) {
		slope = (float) deltaY / (float) deltaX;
	}

	positionOnY0 = y0 - slope * x0;
	// actors are vertical or on a steep slope
	if (absDeltaX < absDeltaY) {
		for (y = y0 + directionY; y != y1; y += directionY) {
			x = x1 == x0 ? x0 : (int) round((y - positionOnY0) / slope);
			if (map.isCellObstructingView(x, y)) {
				actor1SeesActor2 = false;
				break;
			}
		}
	}
	// actors are horizonal or on a gentle slope
	else {
		for (x = x0 + directionX; x != x1; x += directionX) {
			y = (int) round(slope * x + positionOnY0);
			if (map.isCellObstructingView(x, y)) {
				actor1SeesActor2 = false;
				break;
			}
		}
	}

	return actor1SeesActor2;
}
