#include "Window.hpp"

NCurseWindow::~NCurseWindow() {
	if (m_window != 0) {
		delwin(m_window);
	}
}

void NCurseWindow::init(S_Rectangle area) {
	if (m_window != 0) {
		delwin(m_window);
	}
	m_area = area;
	m_window = newwin(area.height, area.width, area.y, area.x);
	box(m_window, 0 , 0);
}

void NCurseWindow::renderChar(int x, int y, char c) {
	mvwprintw(m_window, y, x, "%c", c);
}

void NCurseWindow::renderString(int x, int y, const char *s) {
	mvwprintw(m_window, y, x, s);
}

void NCurseWindow::render() {
	wrefresh(m_window);
}
