#include "FieldOfView.hpp"
#include <algorithm>
#include "Map.hpp"

#define PLAYER_DEPTH_OF_VIEW 20

// Those define the 8 quadrants of a 360 degrees field of vision
static int multipliers[4][8] = {
	{1, 0, 0, -1, -1, 0, 0, 1},
	{0, 1, -1, 0, 0, -1, 1, 0},
	{0, 1, 1, 0, 0, -1, -1, 0},
	{1, 0, 0, 1, -1, 0, 0, -1}
};

FieldOfView::FieldOfView(S_Rectangle visibleArea) : m_visibleArea(visibleArea) {
}

long FieldOfView::_getRelativeIndex(int x, int y) {
	int relativeX = x - m_visibleArea.x,
		relativeY = y - m_visibleArea.y;
	if (relativeX < 0 || relativeX >= m_visibleArea.width ||
		relativeY < 0 || relativeY >= m_visibleArea.height
	) {
		return -1;
	}

	return relativeY * m_visibleArea.width + relativeX;
}

void FieldOfView::_setCellVisible(Map &map, int x, int y) {
	map.setCellVisited(x, y);
	long index = _getRelativeIndex(x, y);
	if (index >= 0) {
		m_vVisibleCells[(unsigned) index] = 1;
	}
}

bool FieldOfView::isVisible(int x, int y) {
	long index = _getRelativeIndex(x, y);
	return index >= 0 && m_vVisibleCells[(unsigned) index] == 1;
}

void FieldOfView::calculate(Map &map, S_Coordinates location) {
	m_vVisibleCells.clear();
	long unsigned sizeView = (unsigned) (m_visibleArea.width * m_visibleArea.height);
	m_vVisibleCells.assign(sizeView, 0);
	_setCellVisible(map, location.x, location.y);
	for (int i = 0; i < 8; ++i) {
		_lightQuadrant(
			map,
			location,
			1,
			1.0,
			0.0,
			multipliers[0][i],
			multipliers[1][i],
			multipliers[2][i],
			multipliers[3][i]
		);
	}
}

// Björn Bergström algorithm,
// http://www.roguebasin.com/index.php?title=FOV_using_recursive_shadowcasting
void FieldOfView::_lightQuadrant(
	Map &map,
	S_Coordinates location, int row,
	double startSlope, double endSlope,
	int xx, int xy, int yx, int yy
) {
	int x = location.x,
		y = location.y;
	if (startSlope < endSlope) {
		return;
	}
	double nextStartSlope = startSlope;
	int depth = PLAYER_DEPTH_OF_VIEW;
	int radius2 = depth * depth;
	for (int i = row; i <= depth; i++) {
		bool blocked = false;
		for (int dx = -i, dy = -i; dx <= 0; dx++) {
			double lSlope = (dx - 0.5) / (dy + 0.5);
			double rSlope = (dx + 0.5) / (dy - 0.5);
			if (startSlope < rSlope) {
				continue;
			} else if (endSlope > lSlope) {
				break;
			}

			int sax = dx * xx + dy * xy;
			int say = dx * yx + dy * yy;
			if ((sax < 0 && (int)std::abs(sax) > x)
				|| (say < 0 && (int)std::abs(say) > y)) {
				continue;
			}
			int ax = x + sax;
			int ay = y + say;
			if (!map.areCoordinatesValid(ax, ay) ||
				ax < m_visibleArea.x ||
				ay < m_visibleArea.y ||
				ax >= m_visibleArea.x + m_visibleArea.width ||
				ay >= m_visibleArea.y + m_visibleArea.height
			) {
				continue;
			}

#ifdef DEBUG
			_setCellVisible(map, ax, ay);
			continue;
#endif

			if ((int) (dx * dx + dy * dy) < radius2) {
				_setCellVisible(map, ax, ay);
			}

			bool cellIsObstructingView = map.isCellObstructingView(ax, ay);
			if (blocked) {
				if (cellIsObstructingView) {
					nextStartSlope = rSlope;
					continue;
				} else {
					blocked = false;
					startSlope = nextStartSlope;
				}
			} else if (cellIsObstructingView) {
				blocked = true;
				nextStartSlope = rSlope;
				_lightQuadrant(map, location, i + 1, startSlope, lSlope, xx,
						xy, yx, yy);
			}
		}
		if (blocked) {
			break;
		}
	}
}

std::vector<std::pair<S_Coordinates, int>> FieldOfView::getVisibleCells(bool full) {
	long unsigned sizeView = m_vVisibleCells.size();
	std::vector<std::pair<S_Coordinates, int>> visible = {};
	for (long unsigned i = 0; i < sizeView; ++i) {
		if (!full && !m_vVisibleCells[i]) {
			continue;
		}

		S_Coordinates c;
		c.x = m_visibleArea.x + (int) i % m_visibleArea.width;
		c.y = m_visibleArea.y + (int) i / m_visibleArea.width;
		visible.push_back(std::make_pair(c, m_vVisibleCells[i]));
	}

	return visible;
}

S_Rectangle &FieldOfView::getVisibleArea() {
	return m_visibleArea;
}
