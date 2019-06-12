#ifndef __GLOBALS__
#define __GLOBALS__

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

#if GCW
const bool FULL_SCREEN = true;
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;
#else
const bool FULL_SCREEN = false;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
#endif
const char * const GAME_DATA_FOLDER = ".rrpg/";
const char * const GAME_START_MAP = "start-map";

#endif
