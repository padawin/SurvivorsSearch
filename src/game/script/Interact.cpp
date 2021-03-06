#include "Interact.hpp"

InteractScript::InteractScript(
	Observable &observable,
	Actor &interactor, Actor &interacted,
	Map &map, int x, int y
) :
	m_observable(observable),
	m_interactor(interactor),
	m_interacted(interacted),
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

int InteractScript::_notify(lua_State *L) {
	int n = lua_gettop(L);
	if (n != 2) {
		return 0;
	}

	Observable *observable = (Observable*) lua_touserdata(L, 1);
	E_Event event = (E_Event) lua_tonumber(L, 2);
	observable->notify(event);
	return 0;
}

void InteractScript::_preRun(lua_State *L) {
	lua_register(L, "map_removeActor", _removeActor);
	lua_register(L, "notify", _notify);
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
