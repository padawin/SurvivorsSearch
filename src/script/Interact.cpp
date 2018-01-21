#include "Interact.hpp"

InteractScript::InteractScript(Map &map, int x, int y) :
	m_map(map),
	m_iX(x),
	m_iY(y)
{
}

void InteractScript::_postRun(lua_State *L) {
	/* the function name */
	lua_getglobal(L, "run");

	/* arguments */
	lua_pushlightuserdata(L, (void*) &m_map);
	lua_pushinteger(L, m_iX);
	lua_pushinteger(L, m_iY);

	int nbArgs = 3,
		nbRes = 0;
	lua_call(L, nbArgs, nbRes);
}
