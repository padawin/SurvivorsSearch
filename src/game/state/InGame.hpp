#ifndef __GAME_STATE__
#define __GAME_STATE__

#include "../../State.hpp"
#include "../Actor.hpp"
#include "../City.hpp"
#include "../../Dialogue.hpp"
#include "../ncurses/Map.hpp"
#include "../ncurses/Actor.hpp"
#include "../ncurses/Window.hpp"
#include "../ncurses/Notifications.hpp"
#include "../../behaviour/Factory.hpp"

class InGame : public State {
	private:
	std::shared_ptr<GameActor> m_player;
	City m_city;
	NCurseWindow m_gameView;
	NotificationWindow m_messagesView;
	NCursesMap m_cityRenderer;
	NCursesActor m_actorRenderer;
	BehaviourFactory m_behaviourFactory;
	S_Rectangle m_camera = {};
	S_Rectangle m_messagesRect = {};
	Dialogue m_dialogues;

	void _renderGame();

	public:
	InGame(UserActions &userActions, Dialogue &dialogues);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
