#ifndef __MAP_CONTENT__
#define __MAP_CONTENT__

#include <vector>

class Actor;

class MapContent {
	private:
	std::vector<Actor*> m_vActors = {};

	public:
	void addActor(Actor *actor);
	std::vector<Actor*> &getActors();
};

#endif
