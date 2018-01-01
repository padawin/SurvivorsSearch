#ifndef __MAP_CONTENT__
#define __MAP_CONTENT__

#include <unordered_map>

class Actor;

class MapContent {
	private:
	std::unordered_map<int, Actor*> m_mActors = {};

	public:
	void addActor(int position, Actor *actor);
	std::unordered_map<int, Actor*> &getActors();
};

#endif
