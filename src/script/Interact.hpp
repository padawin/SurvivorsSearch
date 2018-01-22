#ifndef __INTERACT_SCRIPT__
#define __INTERACT_SCRIPT__

#include "Script.hpp"
#include "../Map.hpp"
#include "../Observable.hpp"

class InteractScript : public Script {
	private:
	Observable &m_observable;
	Map &m_map;
	int m_iX;
	int m_iY;

	static int _removeActor(lua_State *L);

	protected:
	void _preRun(lua_State *L);
	void _postRun(lua_State *L);

	public:
	InteractScript(Observable &observable, Map &map, int x, int y);
};

#endif
