#ifndef __SCRIPT__
#define __SCRIPT__

#include <string>

class Script {
	private:
	static std::string s_sScriptsPath;

	public:
	static void setScriptPath(std::string path);
};

#endif
