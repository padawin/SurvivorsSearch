#ifndef __MAP_CONTENT__
#define __MAP_CONTENT__

#include <unordered_map>
#include <memory>

class Actor;

class MapContent {
	private:
	std::unordered_map<long unsigned, std::shared_ptr<Actor>> m_mActors = {};

	public:
	void addActor(long unsigned position, std::shared_ptr<Actor> actor);
	void removeActor(long unsigned position);
	std::unordered_map<long unsigned, std::shared_ptr<Actor> > &getActors();
	bool moveActor(long unsigned oldPosition, long unsigned newPosition);
	std::shared_ptr<Actor> getActorAt(long unsigned key) const;
};

#endif
