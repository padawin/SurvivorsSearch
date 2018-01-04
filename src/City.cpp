#include "City.hpp"

City::~City() {
	m_vSurvivors.clear();
}

void City::addSurvivor(int cellIndex) {
	m_vSurvivors.push_back(cellIndex);
}
