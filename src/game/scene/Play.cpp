#include "../../FieldOfView.hpp"
#include "../../StateMachine.hpp"
#include "Play.hpp"
#include <iostream>

PlayScene::PlayScene(UserActions &userActions) :
	State(userActions)
{
}

std::string PlayScene::getStateID() const {
	return "PlayScene";
}

bool PlayScene::onEnter() {
	return true;
}

void PlayScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}
}

void PlayScene::render() {
}

void PlayScene::_renderGame() {
}
