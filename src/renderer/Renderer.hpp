#ifndef __RENDERER__
#define __RENDERER__

class Game;

class Renderer {
	public:
	virtual ~Renderer() {}
	virtual bool init(void) const = 0;
	virtual void frame(Game* game) const = 0;
	virtual void shutdown(void) const = 0;
};

#endif
