#ifndef __OBJECT__
#define __OBJECT__

#include "Map.hpp"
#include "types.hpp"

enum E_ObjectType {PROJECTILE};

class Object {
	private:
	E_ObjectType m_eType;

	S_Coordinates m_location = S_Coordinates();

	public:
	Object(E_ObjectType type);
	~Object() {}
	E_ObjectType getType();

	void setX(int x);
	void setY(int y);
	S_Coordinates getLocation();
};

#endif
