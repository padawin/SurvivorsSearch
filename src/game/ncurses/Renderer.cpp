#include "../../Game.hpp"
#include "Renderer.hpp"
#include "renderData.hpp"
#include <ncurses.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

const char FPS = 60;
const int DELAY_TIME = 1000000 / FPS;

bool NCursesRenderer::init(void) const {
	signal(SIGINT, _closeNCurses);
	initscr();
	if (has_colors() && can_change_color()) {
		printf("Has color: %d, can change color: %d\n", has_colors(), can_change_color());
		start_color();
		_initColors();
	}
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	noecho();
	curs_set(FALSE);
	return true;
}

void NCursesRenderer::_initColors() const {
	// for (int c = 0; c < NB_GAME_COLORS; ++c) {
	// 	const short int* color = GAME_COLORS[c];
	// 	init_color(color[0], color[1], color[2], color[3]);
	// }
	init_pair(1, COLOR_RED, COLOR_BLACK);
}

void NCursesRenderer::frame(Game* game) const {
	struct timeval tv;
	long currTime, currTimeAfter, frameTime;
	gettimeofday(&tv,NULL);
	currTime = 1000000 * tv.tv_sec + tv.tv_usec;

	game->loopFrame();
	refresh();

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
