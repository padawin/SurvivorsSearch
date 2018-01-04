#ifndef __GAME_STATE__
#define __GAME_STATE__

#include "../State.hpp"
#include "../Actor.hpp"
#include "../City.hpp"
#include "../ncurses/Map.hpp"
#include "../behaviour/Factory.hpp"

class InGame : public State {
	private:
	Actor m_player;
	City m_city;
	NCursesMap m_cityRenderer;
	BehaviourFactory m_behaviourFactory;

	public:
	InGame(UserActions &userActions);
	bool onEnter();
	void update(StateMachine &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
