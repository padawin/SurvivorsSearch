#include "Window.hpp"

NCurseWindow::~NCurseWindow() {
	if (m_window != 0) {
		delwin(m_window);
	}
}

void NCurseWindow::init(S_Rectangle area) {
	m_area = area;
}

void NCurseWindow::prepareWindow() {
	if (m_window != 0) {
		delwin(m_window);
	}
	m_window = newwin(m_area.height, m_area.width, m_area.y, m_area.x);
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

int NCurseWindow::getWidth() const {
	return m_area.width;
}
