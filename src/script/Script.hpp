#ifndef __SCRIPT__
#define __SCRIPT__

#include <string>

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

class Script {
	private:
	static std::string s_sScriptsPath;

	protected:
	virtual void _preRun(lua_State *L __attribute__((unused))) {}
	virtual void _postRun(lua_State *L __attribute__((unused))) {}

	public:
	virtual ~Script() {}
	static void setScriptPath(std::string path);
	void run(std::string script);
};

#endif
