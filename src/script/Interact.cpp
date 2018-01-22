#include "Interact.hpp"

InteractScript::InteractScript(Observable &observable, Map &map, int x, int y) :
	m_observable(observable),
	m_map(map),
	m_iX(x),
	m_iY(y)
{
}

int InteractScript::_removeActor(lua_State *L) {
	int n = lua_gettop(L);
	if (n != 3) {
		return 0;
	}

	Map *map = (Map*) lua_touserdata(L, 1);
	int x = (int) lua_tonumber(L, 2);
	int y = (int) lua_tonumber(L, 3);
	map->removeActor(x, y);
	return 0;
}

void InteractScript::_preRun(lua_State *L) {
	lua_register(L, "map_removeActor", _removeActor);
}

void InteractScript::_postRun(lua_State *L) {
	/* the function name */
	lua_getglobal(L, "run");

	/* arguments */
	lua_pushlightuserdata(L, (void*) &m_observable);
	lua_pushlightuserdata(L, (void*) &m_map);
	lua_pushinteger(L, m_iX);
	lua_pushinteger(L, m_iY);

	int nbArgs = 4,
		nbRes = 0;
	lua_call(L, nbArgs, nbRes);
}
