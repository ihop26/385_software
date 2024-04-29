#ifndef __GAME
#define __GAME

#include "xil_types.h"
#include "keyboard.h"
#include "hdmi_text_controller.h"

struct GAME_INFO {
	uint64_t sold_ores[100]; //updated every game loop
	uint8_t state; //like in shop, buying, selling, moving etc
    uint64_t money;
    
    uint8_t cursor_x;
    uint8_t cursor_y;
    uint8_t cursor_width;
    uint8_t cursor_height;
    uint16_t cursor_visual [50][50];
    
    uint16_t visual_board [50][50];

    uint32_t functional_board [50][50]
    //todo add more game data
};

//extern keyboard is accessible

struct GAME_INFO game;

void setup_game();

void handle_input(uint8_t buf [4]);

void update_board();

void update_visual(int start_x, int start_y, int end_x, int end_y);

#endif