#include "City.hpp"

City::~City() {
	m_mSurvivors.clear();
}

void City::addSurvivor(int cellIndex, bool saved) {
	m_mSurvivors[cellIndex] = saved;
}
