#ifndef __INTERACT_SCRIPT__
#define __INTERACT_SCRIPT__

#include "../Actor.hpp"
#include "Script.hpp"
#include "../Map.hpp"
#include "../Observable.hpp"

class InteractScript : public Script {
	private:
	Observable &m_observable;
	Actor &m_interactor;
	Actor &m_interacted;
	Map &m_map;
	int m_iX;
	int m_iY;

	static int _removeActor(lua_State *L);
	static int _notify(lua_State *L);

	protected:
	void _preRun(lua_State *L);
	void _postRun(lua_State *L);

	public:
	InteractScript(
		Observable &observable,
		Actor &interactor, Actor &interacted,
		Map &map, int x, int y
	);
};

#endif
