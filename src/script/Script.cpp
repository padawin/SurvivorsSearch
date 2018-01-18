#include "Script.hpp"

std::string Script::s_sScriptsPath = "";

void Script::setScriptPath(std::string path) {
	s_sScriptsPath = path;
}
