#include <limits.h>
#include "Zombie.hpp"
#include "../command/Move.hpp"
#include "../command/Attack.hpp"
#include "../Actor.hpp"
#include <math.h>
#include <algorithm>

BehaviourZombie::BehaviourZombie(std::shared_ptr<Actor> player) : m_player(player) {
}

bool BehaviourZombie::update(Actor *actor, Map &map) {
	bool updated = true;
	S_Coordinates location = m_player->getLocation();
	if (actor->isNextTo(m_player)) {
		AttackCommand command = AttackCommand();
		command.execute(map, location.x, location.y, actor);
		notify(PLAYER_ATTACKED, actor);
	}
	else if (actor->getRace() == LARGE_ZOMBIE && actor->seesActor(map, m_player)) {
		_executeMove(actor, map, location.x, location.y);
	}
	else {
		bool moves = (rand() % 100) > 60;
		if (moves) {
			_executeRandomMove(actor, map);
		}
	}
	return updated;
}

void BehaviourZombie::_executeMove(Actor *actor, Map &map, const int xTarget, const int yTarget) {
	bool executed = false;
	S_Coordinates location = actor->getLocation();
	int xActor = location.x,
		yActor = location.y,
		xDest = xActor,
		yDest = yActor;
	MoveCommand command = MoveCommand();

	// larger Y, move vertically to close the distance
	if (std::abs(xActor - xTarget) < std::abs(yActor - yTarget)) {
		if (yActor < yTarget) {
			++yDest;
		}
		else {
			--yDest;
		}
		executed = command.execute(map, xDest, yDest, actor);
		yDest = yActor;
	}

	// larger X or could not move vertically, move horizontally to close the
	// distance
	if (!executed) {
		if (xActor < xTarget) {
			++xDest;
		}
		else {
			--xDest;
		}
		executed = command.execute(map, xDest, yDest, actor);
	}

	// If could not move towards the player, then move randomly
	if (!executed) {
		_executeRandomMove(actor, map);
	}
}

void BehaviourZombie::_executeRandomMove(Actor *actor, Map &map) {
	MoveCommand command = MoveCommand();
	bool commandExecuted = false;
	S_Coordinates location = actor->getLocation();
	int directions[4] = {0, 1, 2, 3},
		xDest = location.x,
		yDest = location.y;
	std::random_shuffle(directions, directions + 4);
	for (int direction = 3; !commandExecuted && direction--;) {
		switch (directions[direction]) {
			case 0:
				--yDest;
				break;
			case 1:
				++yDest;
				break;
			case 2:
				--xDest;
				break;
			default:
				++xDest;
				break;
		}

		commandExecuted = command.execute(map, xDest, yDest, actor);
	}

	if (actor->getRace() == LARGE_ZOMBIE && actor->seesActor(map, m_player)) {
		notify(PLAYER_SEEN, actor);
	}
}
