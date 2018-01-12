#ifndef __GAME_STATE__
#define __GAME_STATE__

#include "../../State.hpp"
#include "../Actor.hpp"
#include "../City.hpp"
#include "../Notifications.hpp"
#include "../ncurses/Map.hpp"
#include "../ncurses/Actor.hpp"
#include "../ncurses/Window.hpp"
#include "../../behaviour/Factory.hpp"

class InGame : public State {
	private:
	std::shared_ptr<GameActor> m_player;
	City m_city;
	NCurseWindow m_gameView;
	NCursesMap m_cityRenderer;
	NCursesActor m_actorRenderer;
	BehaviourFactory m_behaviourFactory;
	S_Rectangle m_camera = {};
	Notifications m_notifications;

	void _renderGame();

	public:
	InGame(UserActions &userActions);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
