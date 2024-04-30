#ifndef __GAME__H
#define __GAME__H

#define MAX_SHOP_ITEMS 4
#define MAX_SHOP_CATEGORIES 4

#include "xil_types.h"
#include "keyboard.h"
#include "hdmi_text_controller.h"
#include "states.h"
#include "components.h"
#include "shop_text.h"
#include <xgpio.h>
#include "cursor.h"

extern uint8_t flood_board [50][50];

struct GAME_INFO {
	uint64_t sold_ores[100]; //updated every game loop
	uint8_t state; //like in shop, buying, selling, moving etc
    uint64_t money;
    
    uint8_t cursor_locked; //lock cursor in CTRL/MENU states

    uint8_t cursor_x;
    uint8_t cursor_y;
    uint8_t cursor_width;
    uint8_t cursor_height;

    
    
    //store indices into the functional library
    uint8_t cursor_holding;
    block_t cursor [5][5];
    block_t board [50][50];
    block_t snapshot [50][50];

    //stores unique occupied codes for each component
    uint16_t occup_code;
    uint16_t occupied_board [50][50];

    //SHOP VARIABLES
    uint8_t buying;
    int shop_menu_index;
    int shop_index;
    //todo add more game data
};

//extern keyboard is accessible

extern struct GAME_INFO game;

void setup_game();

void update_cursor();

void handle_input(uint8_t buf [4]);

void update_board(int start_x, int start_y, int end_x, int end_y);

void update_states();

void update_right_text();


#endif
