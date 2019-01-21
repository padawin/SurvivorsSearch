#ifndef __FIELD_OF_VIEW__
#define __FIELD_OF_VIEW__

#include "types.hpp"
#include <vector>
#include <memory>

class Map;

const int FLAG_VISITED = 0;
const int FLAG_VISIBLE = 1;

class FieldOfView {
	private:
	std::vector<int> m_vVisibleCells = {};
	S_Rectangle m_visibleArea;

	void _lightQuadrant(
		Map *map,
		S_Coordinates location, int row,
		double startSlope, double endSlope,
		int xx, int xy, int yx, int yy
	);
	long _getRelativeIndex(int x, int y);
	void _setCellVisible(Map *map, int x, int y);

	public:
	FieldOfView(S_Rectangle visibleArea);
	void calculate(Map *map, S_Coordinates location);
	std::vector<std::pair<S_Coordinates, int>> getVisibleCells(bool full);
	S_Rectangle &getVisibleArea();
	bool isVisible(int x, int y);
};

#endif
