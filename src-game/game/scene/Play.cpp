#include "../../FieldOfView.hpp"
#include "../../StateMachine.hpp"
#include "../../Game.hpp"
#include "../../globals.hpp"
#include "../Cave.hpp"
#include "Play.hpp"
#include "GameOver.hpp"
#include <iostream>

PlayScene::PlayScene(UserActions &userActions) :
	State(userActions),
	m_actorFactory(ActorFactory()),
	m_player(m_actorFactory.createActor(RACE_HUMAN, PLAYER)),
	m_map(std::shared_ptr<Map>(new Cave())),
	m_mapRenderer(SDL2Map()),
	m_actorRenderer(SDL2Actor())
{
}

std::string PlayScene::getStateID() const {
	return "PlayScene";
}

bool PlayScene::onEnter() {
	m_camera.x = 0;
	m_camera.y = 0;
	m_camera.width = SCREEN_WIDTH;
	m_camera.height = SCREEN_HEIGHT;
	m_mapRenderer.setCamera(m_camera);
	return 1;
}

void PlayScene::update(StateMachine &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}

	auto actors = m_map->getActors();

	if (!m_player->update(m_map.get())) {
		return;
	}
	for (auto it = actors.begin(); it != actors.end(); ++it) {
		if (it->second != m_player) {
			it->second->update(m_map.get());
		}
	}

	if (m_player->isDead()) {
		stateMachine.changeState(new GameOverScene(m_userActions));
	}
}

void PlayScene::render(const Renderer *renderer) {
	S_Coordinates center = m_player->getLocation();
	// x,y coords in the grid
	int cameraWidthGrid = m_camera.width / TILE_WIDTH;
	int cameraHeightGrid = m_camera.height / TILE_HEIGHT;

	// portion of the map which is visible
	S_Rectangle visibleArea;
	visibleArea.x = center.x - cameraWidthGrid / 2;
	visibleArea.y = center.y - cameraHeightGrid / 2;
	visibleArea.width = cameraWidthGrid;
	visibleArea.height = cameraHeightGrid;
	FieldOfView fov(visibleArea);
	fov.calculate(m_map.get(), center);
	int shiftX = 1 + m_camera.x - visibleArea.x;
	int shiftY = 1 + m_camera.y - visibleArea.y;
	m_mapRenderer.render(renderer, m_map.get(), fov, shiftX, shiftY);
	for (auto actor : m_map->getActors()) {
		m_actorRenderer.render(actor.second, fov, shiftX, shiftY);
	}
	// render HUD
	// HUD::render(m_game, m_player);
}

void PlayScene::_renderGame() {
}
