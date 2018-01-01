#ifndef __MAP__
#define __MAP__

class Map {
	protected:
	int width = 0;
	unsigned int size = 0;
	char *grid = 0;

	public:
	int getWidth();
	unsigned int getSize();
};

#endif
