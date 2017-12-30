#ifndef __STATE__
#define __STATE__

#include <string>

/**
 * Each scene is a game state, provided in the game state machine.
 * Each State has a list of objects and of renderable objects.
 *
 * Each state can be updated (at each game loop iteration), rendered, has an ID
 * (to differenciate it from another state) and has two hooks (one when the
 * machine enters the state and one when the machine leaves it).
 */
class State {
	public:
	virtual	~State() {}
	virtual void update() = 0;
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const = 0;
};

#endif
