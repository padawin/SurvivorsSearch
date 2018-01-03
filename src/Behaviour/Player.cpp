#include "Player.hpp"
#include "../UserActions.hpp"
#include "../Actor.hpp"
#include "../Map.hpp"
#include "../Command/Move.hpp"
#include "../Command/Attack.hpp"

BehaviourPlayer::BehaviourPlayer(UserActions &userActions) :
	m_userActions(userActions)
{
}

bool BehaviourPlayer::update(Actor *actor, Map &map) {
	bool updated = false;
	updated = _actionDirection(actor, map);

	return updated;
}

bool BehaviourPlayer::_actionDirection(Actor *actor, Map &map) {
	bool updated = false,
		 directionPressed = false;
	S_Coordinates location = actor->getLocation();
	int xDest = location.x,
		yDest = location.y;
	directionPressed = _isDirectionPressed(xDest, yDest);

	if (directionPressed) {
		updated = _tryMove(actor, map, xDest, yDest);
		if (!updated) {
			updated = _tryAttack(actor, map, xDest, yDest);
		}
	}

	return updated;
}

bool BehaviourPlayer::_isDirectionPressed(int &x, int &y) {
	bool directionPressed = false;
	if (m_userActions.getActionState("MOVE_PLAYER_UP")) {
		--y;
		directionPressed = true;
	}
	else if (m_userActions.getActionState("MOVE_PLAYER_DOWN")) {
		++y;
		directionPressed = true;
	}
	else if (m_userActions.getActionState("MOVE_PLAYER_LEFT")) {
		--x;
		directionPressed = true;
	}
	else if (m_userActions.getActionState("MOVE_PLAYER_RIGHT")) {
		++x;
		directionPressed = true;
	}

	return directionPressed;
}

bool BehaviourPlayer::_tryMove(Actor *actor, Map &map, int x, int y) {
	MoveCommand command = MoveCommand();
	bool moved = command.execute(actor, map, x, y);

	return moved;
}

bool BehaviourPlayer::_tryAttack(Actor *actor, Map &map, int x, int y) {
	Actor* target = map.getActorAt(x, y);
	if (target == NULL) {
		return false;
	}

	AttackCommand attack = AttackCommand();
	return attack.execute(actor, map, x, y);
}
