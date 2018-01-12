#ifndef __CITY__
#define __CITY__

#include <vector>
#include "types.hpp"
#include "../Map.hpp"

class City : public Map {
	friend class CityGenerator;
	friend class Save;
	protected:
	S_CityInfo m_info = S_CityInfo();

	public:
	void update();
	int getWidth() const { return 530; }
	int getHeight() const { return 230; }
};

#endif