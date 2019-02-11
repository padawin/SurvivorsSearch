#ifndef __GAME_STATE__
#define __GAME_STATE__

#include "../../State.hpp"
#include "../../Actor.hpp"
#include "../../ActorFactory.hpp"
#include "../sdl2/Map.hpp"
#include "../sdl2/Actor.hpp"

class PlayScene : public State {
	private:
	ActorFactory m_actorFactory;
	std::shared_ptr<Actor> m_player;
	std::shared_ptr<Map> m_map;
	//rRpg m_engine;
	// NCurseWindow m_gameView;
	// NotificationWindow m_messagesView;
	// DialogueWindow m_dialogueView;
	SDL2Map m_mapRenderer;
	SDL2Actor m_actorRenderer;
	// BehaviourFactory m_behaviourFactory;
	S_Rectangle m_camera = {};

	void _renderGame();

	public:
	PlayScene(UserActions &userActions);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render(const Renderer *renderer);
	std::string getStateID() const;
};

#endif
