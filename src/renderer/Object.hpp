#ifndef __OBJECT_RENDERER__
#define __OBJECT_RENDERER__

#include <memory>
#include "../FieldOfView.hpp"

class Object;
class ObjectRenderer {
	public:
	virtual ~ObjectRenderer() {}
	virtual void render(std::shared_ptr<Object> object, FieldOfView &fov, int displayShiftX, int displayShiftY) = 0;
};

#endif
