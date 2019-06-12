#ifndef __SAVE__
#define __SAVE__

#include <memory>
#include "../game/Save.hpp"

class Save : public AbstractSave {
	private:
	std::shared_ptr<Actor> m_player;
	std::shared_ptr<Map> m_map;

	bool _loadStartMap();
	bool _loadMapAtLevel(std::string mapName, int level);
	bool _loadMap(std::string mapFile, S_MapSpecs specs);
	void _placePlayerOnMap();

	public:
	Save(std::shared_ptr<Actor> player, std::shared_ptr<Map> map);
	bool exists();
	void load();
	void create();
};

#endif
