#include "game.h"

struct GAME_INFO game;

/////////////////////////////////////////////////////////////
/*         TODO LIST                                       */
/*       1. add states to the game      DONE               */
/*       2. add simple shop functionality   DONE           */
/*       3. add ability to select & delete components DONE      */
/*       4. when selecting components can move it around  DONE  */
/*       5. money counter                                  DONE*/
/*       6. rotation of simple components                 DONE */
/*       7. add support for composite components           DONE*/
/*            (figure out a good way to store this)        */
/*       10. finish upgraders                              */
/*       11. finish furnaces                               */
/*       8. prestige                                       */
/*       9. polish game                                    */
/////////////////////////////////////////////////////////////

/*
    SETUP GAME
    Inputs: none
    Outputs: none
    Effects: sets up the game with default states, is called once at the start of programming
*/
void setup_game(){
    setup_keyboard();
    initialize_shop();

    for(int i = 0; i<50; i++){
        for(int j = 0; j<50; j++){
            game.snapshot[i][j] = (block_t){0};
            game.board[i][j] =  (block_t){0};
            game.occupied_board[i][j] = 0;
        }
        game.sold_ores[i*2] = 0;
        game.sold_ores[i*2 + 1] = 0;
    }
    for(int i = 0; i<5; i++){
        for(int j = 0; j<5; j++){
            game.cursor[i][j] = (block_t){0};
        }
    }
    uint64_t initial_mine = 0x0000808500001040;
    setMine(0,initial_mine);
    game.buying = 0;
    game.cursor_holding = 0;
    game.occup_code = 1;
    game.cursor_x = 0;
    game.cursor_y = 0;
    game.cursor_width = 1;
    game.cursor_height = 1;
    game.cursor[0][0] = (block_t){5,0,0};
    game.money = 50;
    game.state = STATE_MENU;
    game.shop_index = 0;
    game.shop_menu_index = 0;
    //todo set palette
    //generic w/b colors
    setColorPalette(0, 	0, 0, 0);
	setColorPalette(1, 0x8, 0x8, 0x8);

    //dark grey
    setColorPalette(2, 0x4, 0x4, 0x4);
    setColorPalette(3, 0x7, 0x7, 0x7);
	
	//furnace 
	setColorPalette(4, 0xF, 0x4, 0x4);
	//upgrader
	setColorPalette(5,0x0,0xF,0xF);
    //grass
    setColorPalette(10,0x6,0xC,0x0);
    setColorPalette(11,0x4,0x8,0x0);
    //colision/ore colors
    setColorPalette(12, 0x0,0xF,0xF);
    setColorPalette(13, 0xF,0xF,0x0);
    setColorPalette(14, 0x8, 0x0, 0x0);
    setColorPalette(15, 0x0, 0x8, 0x0);

    for(int i = 0; i<5; i++){
        setBottomText(bottom_text[i],0, i, 0, 1);
    }

    update_right_text();
    update_board(0,0,49,49);
    //todo make a basic startup screen
}

/*
    HANDLE INPUT
    Inputs: buffer, stores the 4 keys currently pressed using scancodes
    Outputs: none
    Effects: first calls update keyboard struct to update key press states
    then calls various other functions to deal with the new key states
*/
void handle_input(uint8_t buf [4]){
    update_keyboard_state(buf);
    //UPDATE CURSOR STUFF
    update_cursor();
    //TODO UPDATE STATES ETC
    update_states();

   update_money();
}

/*
    UPDATE_BOARD
    inputs: a rectangle of area to update
    outputs: none
    effects: rewrites the visual BRAM within the rectangle, used to selectively update the screen
*/
void update_board(int start_x, int start_y, int end_x, int end_y){
    //todo updates from startx->endx and starty->endy
    if(start_x > end_x || start_y > end_y){
        return;
    }
    if(start_x < 0) start_x = 0;
    if(start_y < 0) start_y = 0;
    if(end_x > 49) end_x = 49;
    if(end_y > 49) end_y = 49;

    uint8_t i; 
    uint8_t j;
    for(i = start_x; i<=end_x; i++){
        for(j = start_y; j<=end_y; j++){
            //(if cursor_visual[i-cursor_x][j-cursor_y] != 0) draw cursor @ ij
            //else draw visual board[i][j] @ ij
            if((i < game.cursor_x + game.cursor_width) && (i >= game.cursor_x)
            		&& (j < game.cursor_y + game.cursor_height) && (j >= game.cursor_y)
					&& (game.cursor[i-game.cursor_x][j-game.cursor_y].type != BLANK_T)){

                uint16_t visual = get_visual(game.cursor[i-game.cursor_x][j-game.cursor_y]);
                if(visual!=1){
                	if(game.occupied_board[i][j] == 0){//set green
                	     visual = (visual & 0xFF00) | 0xF0;
                	}else{//set red if overlap
                	     visual = (visual & 0xFF00) | 0xE0;
                	}
                }
                setVisual(visual, i, j);
            }else{
                uint16_t visual = get_visual(game.board[i][j]);
                setVisual(visual, i, j);
            }
            uint32_t board = get_functional(game.board[i][j]);
            setBoard(board,i,j);
        }
    }
}


/*
    UPDATE_CURSOR
    inputs none
    outputs none
    effects: moves around cursor according to the keyboard struct
*/
void update_cursor(){

    if(game.cursor_locked) return;

    if(pressed(W_KEY) || held(W_KEY)){
        if(game.cursor_y > 0 && (game.cursor_y+game.cursor_height-1) < 50) game.cursor_y--;
    }
    if(pressed(S_KEY) || held(S_KEY)){
        if(game.cursor_y > -1 && (game.cursor_y+game.cursor_height-1) < 49) game.cursor_y++;
    }
    if(pressed(D_KEY) || held(D_KEY)){
        if(game.cursor_x > -1 && (game.cursor_x+game.cursor_width-1) < 49) game.cursor_x++;
    }
    if(pressed(A_KEY) || held(A_KEY)){
        if(game.cursor_x > 0 && (game.cursor_x+game.cursor_width-1) < 50) game.cursor_x--;
    }
    update_board((game.cursor_x-1),(game.cursor_y-1),(game.cursor_x+game.cursor_width+1),(game.cursor_y+game.cursor_height+1));
}
/*
    UPDATE_STATES
    inputs none
    outputs none
    effects: giant state machine, navigates between shop, menu, controls, etc, locks certain features in states
*/
void update_states(){
    int right_bar_changed = 0;
    int pressed_space = pressed(SPACE);
    int pressed_esc = pressed(ESCAPE);
    int pressed_r = pressed(R_KEY);
    int pressed_delete = pressed(DELETE);

    //cheat in money
    if(pressed(INF)){
        game.money = 0xFFFFFFFFFFFF;
    }

    if(pressed_space && !game.cursor_locked){
        if(game.cursor_holding){//try to place
            if(place_cursor() != 0){
                dump_cursor();
                pressed_space = 0; // succeeded (use up action)
            } 
            clear_snapshot();
        	game.buying = 0;
        }else{//try to grab
            component_t cut = cut_snapshot(game.cursor_x,game.cursor_y);
            if(cut.width != 0){
                fill_cursor(cut);
                pressed_space = 0; //succeeded (use up action)
            }
        }
    }
    
    //if pressed delete, dump cursor and delete snapshot
    if(pressed_delete && game.cursor_holding){
        pressed_delete = 0;
        dump_cursor();
        clear_snapshot();
    }

    if(pressed_esc && game.cursor_holding){//dump whatever you have
        pressed_esc = 0; //use up action if holding
        if(!game.buying){
            paste_snapshot();
            clear_snapshot();
        }
    	dump_cursor();
    }

    if(pressed_r && game.cursor_holding){
    	pressed_r = 0;
    	rotate_cursor();
    }
    
    switch(game.state){
        case STATE_MENU:
            game.cursor_locked = TRUE;
            if(pressed(UP)){
                right_bar_changed = 1;
                game.menu_index = ((game.menu_index-1)+2)%2;
                xil_printf("%d",game.menu_index);
            }else if(pressed(DOWN)){
                right_bar_changed = 1;
                game.menu_index = ((game.menu_index+1)+2)%2;
                xil_printf("%d",game.menu_index);

            }else if(pressed(ENTER)){
                right_bar_changed = 1;
                if(game.menu_index == 0){
                    game.state = STATE_SHOP_MENU;
                }else if(game.menu_index == 1){
                    game.state = STATE_CTRL;
                }
            }
            break;
        case STATE_SHOP_MENU: //shop menu has 4 categories: conveyors, mines, upgraders, furnaces
            game.cursor_locked = FALSE;
            game.shop_index = 0;
            if(pressed_esc){
                right_bar_changed = 1;
                game.state = STATE_MENU;
            } else if(pressed(UP)){
                right_bar_changed = 1;
                game.shop_menu_index = ((game.shop_menu_index-1)+MAX_SHOP_CATEGORIES)%MAX_SHOP_CATEGORIES;
            } else if(pressed(DOWN)){
                right_bar_changed = 1;
                game.shop_menu_index = ((game.shop_menu_index+1)+MAX_SHOP_CATEGORIES)%MAX_SHOP_CATEGORIES;
            } else if(pressed(ENTER)){
                right_bar_changed = 1;
                game.state = STATE_SHOP;
            }
            break;  
        case STATE_SHOP: //shop menu for individual categories, index through
            game.cursor_locked = FALSE;
            if(pressed_esc){
                right_bar_changed = 1;
                game.state = STATE_SHOP_MENU;
            }else if(pressed(UP)){
                right_bar_changed = 1;
                game.shop_index = ((game.shop_index-1)+MAX_SHOP_ITEMS)%MAX_SHOP_ITEMS;
            }else if(pressed(DOWN)){
                right_bar_changed = 1;
                game.shop_index = ((game.shop_index+1)+MAX_SHOP_ITEMS)%MAX_SHOP_ITEMS;
            }else if(pressed(ENTER)){
                if(!game.cursor_holding && game.money >= shop_prices[game.shop_menu_index][game.shop_index]){
                    game.buying = 1;
                    game.money -= shop_prices[game.shop_menu_index][game.shop_index];
                    fill_cursor(shop_library[game.shop_menu_index][game.shop_index]);
                }
            } 
            break;
        case STATE_CTRL:
            game.cursor_locked = TRUE;
            if(pressed_esc){
                right_bar_changed = 1;
                game.state = STATE_MENU;
            }
            break;
    }

    if(right_bar_changed == 1){
        update_right_text();
    }
}

void update_right_text(){
	int foreground = 1;
    switch(game.state){
        case STATE_MENU:
            for(int i = 0; i<30; i++){
                setRightText(menu_text[i],0,i,0,1);
            }
            for(int i = 0; i<2; i++){
                foreground = 1;
                if(game.menu_index == i){
                    foreground = 15;
                }
                setRightText(menu_items[i],0,(5+i*4),0,foreground);
            }
            break;
        case STATE_SHOP_MENU:
            for(int i = 0; i<30; i++){
                setRightText(shop_menu_text[i],0,i,0,1);
            }
            for(int i = 0; i<MAX_SHOP_CATEGORIES; i++){
                foreground = 1;
                if(game.shop_menu_index == i){
                    foreground = 15;
                }
                setRightText(shop_menu_items[i],0,(5+i*4),0,foreground);
            }
            break;
        case STATE_SHOP:
            for(int i = 0; i<30; i++){
                setRightText(shop_text[i],0,i,0,1);
            }
            for(int i = 0; i<MAX_SHOP_ITEMS; i++){
                foreground = 1;
                if(game.shop_index == i){
                    foreground = 15;
                }
                setRightText(shop_items[game.shop_menu_index][i],0,(5+i*3),0,foreground);
            }
            break;
        case STATE_CTRL:
            for(int i = 0; i<30; i++){
                setRightText(controls_text[i],0,i,0,1);
            }
            break;
    }
}
void update_money(){
	uint8_t ore[8];
	for(int i = 0; i<100; i++){
		if(!getOre(i,ore)) continue;
		uint32_t top = (ore[7]<<24) | (ore[6] << 16) | (ore[5] << 8) | ore[4];
		xil_printf("%x\n",top);
		uint32_t base = ((top << 1) & 0xFFFF0000) >> 16;
		uint32_t multiplier = ((top << 17) & 0xFF000000) >> 24;
		uint32_t exponent = ((top << 25) & 0xF8000000) >> 27;
		game.money += (base*(multiplier+1)) << exponent;
		xil_printf("%d: %d %d %d\n",i,base,multiplier,exponent);
	}
	//xil_printf("%ld\n",game.money);
    update_m_string();
    setBottomText(game.m_string, 15, 2, 0, 1);

}

void update_m_string(){
    uint64_t mon = game.money;

    int ctr = 1;
    for(int i = 0; i<21; i++){
        game.m_string[i] = ' ';
    }
    game.m_string[20] = mon%10+48;
    mon = mon/10;
    while(mon > 0 && ctr < 20){
        game.m_string[20-ctr] = mon%10 + 48;
        mon = mon/10;
        ctr++;
    }
   game.m_string[20-ctr] = '$';
   game.m_string[21] = '\0';
}
