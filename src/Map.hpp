#ifndef __MAP__
#define __MAP__

class Map {
	protected:
	int width = 0;
	unsigned int size = 0;
	char *grid = 0;

	public:
	virtual ~Map() {}
	int getWidth();
	unsigned int getSize();
	virtual unsigned char getCell(const int x, const int y) const;
};

#endif
