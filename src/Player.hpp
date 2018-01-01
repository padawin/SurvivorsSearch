#ifndef __PLAYER__
#define __PLAYER__

#include "types.hpp"

class Player {
	friend class Save;
	private:
	char m_sCity[20];
	S_Coordinates m_location = S_Coordinates();
	int m_iHealth = 3;
	int m_iMaxHealth = 3;

	public:
	char* getCity();
	S_Coordinates getLocation();
};

#endif
