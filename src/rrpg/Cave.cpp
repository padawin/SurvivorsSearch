#include "Cave.hpp"

MyUnorderedMap<E_MapType, std::vector<S_EnemyProbability>> Cave::s_mEnemiesPerMapType = MyUnorderedMap<E_MapType, std::vector<S_EnemyProbability>>({});


Cave::~Cave() {
}

Terrain *Cave::_getTerrain(E_TerrainType type) {
	if (m_mTerrains.find(type) == m_mTerrains.end()) {
		Terrain *terrain = new Terrain();
		if (TERRAIN_GRASS_NORMAL == type) {
			terrain->setFlags(Terrain::TERRAIN_FLAG_WALKABLE);
		}
		else if (TERRAIN_SOIL_NORMAL == type) {
			terrain->setFlags(
				Terrain::TERRAIN_FLAG_WALKABLE | Terrain::TERRAIN_FLAG_BASE
			);
		}
		else if (TERRAIN_ROCK_NORMAL == type) {
			terrain->setFlags(Terrain::TERRAIN_FLAG_OBSTRUCTING_VIEW);
		}

		m_mTerrains[type] = terrain;
	}

	return m_mTerrains[type];
}
