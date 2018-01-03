#ifndef __STATE_MACHINE__
#define __STATE_MACHINE__

#include "State.hpp"
#include <vector>
#include "UserActions.hpp"

/**
 * Finished state machine. Contains a stack of states.
 * A new state can be pushed on top of the stack, the top state can be changed
 * for another one and the top state can also be popped.
 */
class StateMachine {
	private:
	std::vector<State*> m_vStates = {};
	UserActions &m_userActions;

	public:
	StateMachine(UserActions &userActions);
	void pushState(State* pState);
	void changeState(State* pState);
	bool popState();
	void clean();
	State* getCurrentState() const;
	UserActions &getUserActions() const;

	/**
	 * Methods to update and render the current state
	 */
	void update();
	void render() const;
};

#endif
