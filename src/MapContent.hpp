#ifndef __MAP_CONTENT__
#define __MAP_CONTENT__

#include <unordered_map>
#include <memory>

class Actor;

class MapContent {
	private:
	std::unordered_map<int, std::shared_ptr<Actor>> m_mActors = {};

	public:
	void addActor(int position, std::shared_ptr<Actor> actor);
	std::unordered_map<int, std::shared_ptr<Actor> > &getActors();
	bool moveActor(int oldPosition, int newPosition);
	std::shared_ptr<Actor> getActorAt(int key) const;
};

#endif
