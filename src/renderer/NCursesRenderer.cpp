#include "NCursesRenderer.hpp"
#include "../Game.hpp"
#include <curses.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

const char FPS = 10;
const int DELAY_TIME = 1000000 / FPS;

bool NCursesRenderer::init(void) const {
	signal(SIGINT, _closeNCurses);
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	noecho();
	curs_set(FALSE);
	return true;
}

void NCursesRenderer::frame(Game* game) const {
	struct timeval tv;
	long currTime, currTimeAfter, frameTime;
	gettimeofday(&tv,NULL);
	currTime = 1000000 * tv.tv_sec + tv.tv_usec;

	clear();
	game->loopFrame();

	// use a delay to cap the fps
	gettimeofday(&tv,NULL);
	currTimeAfter = 1000000 * tv.tv_sec + tv.tv_usec;
	frameTime = currTimeAfter - currTime;
	if (frameTime < DELAY_TIME) {
		usleep((unsigned) (DELAY_TIME - frameTime));
	}
}

void NCursesRenderer::shutdown(void) const {
	_closeNCurses(0);
}

void NCursesRenderer::_closeNCurses(int code __attribute__((unused))) {
	echo();
	keypad(stdscr, FALSE);
	nodelay(stdscr, FALSE);
	nocbreak();
	endwin();
}
