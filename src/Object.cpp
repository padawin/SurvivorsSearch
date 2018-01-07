#include "Object.hpp"

Object::Object(E_ObjectType type) :
	m_eType(type)
{
}

E_ObjectType Object::getType() { return m_eType; }

S_Coordinates Object::getLocation() { return m_location; }

void Object::setX(int x) { m_location.x = x; }
void Object::setY(int y) { m_location.y = y; }
