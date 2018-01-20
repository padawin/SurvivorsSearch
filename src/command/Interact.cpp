#include <string.h>
#include "Interact.hpp"
#include "../Map.hpp"
#include "../script/Interact.hpp"
#include "../Actor.hpp"

bool InteractCommand::execute(Map &map, int xDest, int yDest, Actor* actor) {
	std::string scriptFile = actor->getScript();
	if (scriptFile != "") {
		InteractScript s = InteractScript(map, xDest, yDest);
		s.run(scriptFile);
	}
	return true;
}
