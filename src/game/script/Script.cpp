#include "Script.hpp"

std::string Script::s_sScriptsPath = "";

void Script::setScriptPath(std::string path) {
	s_sScriptsPath = path;
}

void Script::run(std::string script) {
	/* the Lua interpreter */
	lua_State* L;
	/* initialize Lua */
	L = luaL_newstate();
	/* load Lua base libraries */
	luaL_openlibs(L);

	_preRun(L);
	/* run the script */
	std::string file = s_sScriptsPath + "/" + script + ".lua";
	int res = luaL_dofile(L, file.c_str());
	if (res) {
		fprintf(stderr, "Script %s not executed: %d\n", file.c_str(), res);
		fprintf(stderr, "cannot run configuration file: %s\n", lua_tostring(L, -1));
	}

	_postRun(L);

	/* cleanup Lua */
	lua_close(L);
}
