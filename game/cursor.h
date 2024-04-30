#ifndef __CURSOR
#define __CURSOR

#include "components.h"
#include "game.h"

int fill_cursor(component_t filler);
int place_cursor();
int dump_cursor();
int rotate_cursor();

int flood_select(int x, int y, int key);

component_t cut_snapshot(int x, int y);
int paste_snapshot();
int clear_snapshot();

#endif