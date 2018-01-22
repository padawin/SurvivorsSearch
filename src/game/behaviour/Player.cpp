#include "Player.hpp"
#include "../../UserActions.hpp"
#include "../Actor.hpp"
#include "../../Map.hpp"
#include "../command/Move.hpp"
#include "../command/Open.hpp"
#include "../command/Attack.hpp"
#include "../../script/Interact.hpp"

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
			updated = _tryOpen(map, xDest, yDest);
		}
		if (!updated) {
			updated = _tryInteractActor(actor, map, xDest, yDest);
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
	bool moved = command.execute(map, x, y, actor);

	return moved;
}

bool BehaviourPlayer::_tryOpen(Map &map, int x, int y) {
	OpenCommand command = OpenCommand();
	bool moved = command.execute(map, x, y);

	return moved;
}

bool BehaviourPlayer::_tryInteractActor(Actor *actor, Map &map, int x, int y) {
	std::shared_ptr<Actor> target = map.getActorAt(x, y);
	bool res = true;
	if (target == NULL) {
		res = false;
	}
	else if (target->getType() == FOE) {
		AttackCommand attack = AttackCommand();
		res = attack.execute(map, x, y, actor);
		notify(PLAYER_ATTACK, target.get());
	}
	else {
		std::string scriptFile = target->getScript();
		if (scriptFile != "") {
			InteractScript s = InteractScript(*this, map, x, y);
			s.run(scriptFile);
		}
		if (target->getType() == SURVIVOR) {
			notify(SURVIVOR_SAVED, target.get());
		}
	}

	return res;
}
