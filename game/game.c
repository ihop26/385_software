#include "game.h"
#include "shop_text.h"

struct GAME_INFO game;

/////////////////////////////////////////////////////////////
/*         TODO LIST                                       */
/*       1. add states to the game                         */
/*       2. add simple shop functionality                  */
/*       3. add ability to select & sell components        */
/*       4. when selecting components can move it around   */
/*       5. money counter                                  */
/*       6. rotation of simple components                  */
/*       7. add support for composite components           */
/*            (figure out a good way to store this)        */
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
    for(int i = 0; i<50; i++){
        for(int j = 0; j<50; j++){
            game.cursor_visual[i][j] = 0;
            game.visual_board[i][j] = 0;
            game.functional_board[i][j] = 0;
        }
        game.sold_ores[i*2] = 0;
        game.sold_ores[i*2 + 1] = 0;
    }
    game.occup_code = 0;
    game.cursor_x = 0;
    game.cursor_y = 0;
    game.cursor_width = 0;
    game.cursor_height = 0;
    game.cursor_visual[0][0] = 0x0001;
    game.money = 0;
    game.state = STATE_MENU;

    //todo set palette
    setColorPalette(0, 	0, 0, 0);
	setColorPalette(1, 0x8, 0x8, 0x8);
    setColorPalette(2, 0x0, 0x8, 0x0);
    setColorPalette(13, 0xF,0x6,0xF);
    update_right_text();
    update_visual(0,0,49,49);
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
    //printf("%d %d \n", game.cursor_x, game.cursor_y);
}

/*
    UPDATE_VISUAL
    inputs: a rectangle of area to update
    outputs: none
    effects: rewrites the visual BRAM within the rectangle, used to selectively update the screen
*/
void update_visual(int start_x, int start_y, int end_x, int end_y){
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
            if((game.cursor_x <= i) && (game.cursor_y <= j) && (game.cursor_visual[i-game.cursor_x][j-game.cursor_y])){
                setVisual(game.cursor_visual[i-game.cursor_x][j-game.cursor_y], i, j);
            }else{
                setVisual(game.visual_board[i][j], i, j);
            }
        }
    }
}
/*
    UPDATE_BOARD
*/
void update_board(){
    //todo update dynamic stuff
}

/*
    UPDATE_CURSOR
    inputs none
    outputs none
    effects: moves around cursor according to the keyboard struct
*/
void update_cursor(){

    if(game.cursor_locked) return;

    if(pressed(UP) || held(UP)){
        if(game.cursor_y > 0 && (game.cursor_y+game.cursor_height) < 50) game.cursor_y--;
    }
    if(pressed(DOWN) || held(DOWN)){
        if(game.cursor_y > -1 && (game.cursor_y+game.cursor_height) < 49) game.cursor_y++;
    }
    if(pressed(RIGHT) || held(RIGHT)){
        if(game.cursor_x > -1 && (game.cursor_x+game.cursor_width) < 49) game.cursor_x++;
    }
    if(pressed(LEFT) || held(LEFT)){
        if(game.cursor_x > 0 && (game.cursor_x+game.cursor_width < 50)) game.cursor_x--;
    }
    update_visual((game.cursor_x-1),(game.cursor_y-1),(game.cursor_x+game.cursor_width+1),(game.cursor_y+game.cursor_height+1));
}
/*
    UPDATE_STATES
    inputs none
    outputs none
    effects: giant state machine, navigates between shop, menu, controls, etc, locks certain features in states
*/
void update_states(){
    printf("%d",game.state);
    int right_bar_changed = 0;
    switch(game.state){
        case STATE_MENU:
            game.cursor_locked = TRUE;
            if(pressed(B_KEY)){
                right_bar_changed = 1;
                game.state = STATE_SHOP;
            } else if(pressed(C_KEY)){
                right_bar_changed = 1;
                game.state = STATE_CTRL;
            } 
            break;
        case STATE_SHOP_MENU: //shop menu has 4 categories: conveyors, mines, upgraders, furnaces
            game.cursor_locked = FALSE;
            game.shop_index = 0;
            if(pressed(ESCAPE)){
                right_bar_changed = 1;
                game.state = STATE_MENU;
            } else if(pressed(W_KEY)){ 
                right_bar_changed = 1;
                game.shop_menu_index = (game.shop_menu_index-1)%MAX_SHOP_CATEGORIES;
            } else if(pressed(S_KEY)){
                right_bar_changed = 1;
                game.shop_menu_index = (game.shop_menu_index+1)&MAX_SHOP_CATEGORIES;
            } else if(pressed(SPACE)){
                right_bar_changed = 1;
                game.state = STATE_SHOP;
            }
            break;  
        case STATE_SHOP: //shop menu for individual categories, index through
            if(pressed(ESCAPE)){
                right_bar_changed = 1;
                game.state = STATE_SHOP_MENU;
            }else if(pressed(W_KEY)){
                right_bar_changed = 1;
                game.shop_index = (game.shop_index-1)%MAX_SHOP_ITEMS;
            }else if(pressed(S_KEY)){
                right_bar_changed = 1;
                game.shop_index = (game.shop_index+1)%MAX_SHOP_ITEMS;
            }else if(pressed(SPACE)){
                //todo buy shit
            }
            break;
        case STATE_CTRL:
            game.cursor_locked = TRUE;
            if(pressed(ESCAPE)){
                right_bar_changed = 1;
                game.state = STATE_MENU;
            }
            break;
        case STATE_BUY:
            game.cursor_locked = FALSE;
            if(pressed(ESCAPE)){
                game.state = STATE_SHOP;
            }
            break;
        case STATE_SELECT:
            game.cursor_locked = FALSE;
            if(pressed(ESCAPE)){
                game.state = STATE_SHOP;
            }
            break;
    }

    if(right_bar_changed == 1){
        update_right_text();
    }
}

void update_right_text(){
    switch(game.state){
        case STATE_MENU:
            for(int i = 0; i<30; i++){
                setRightText(menu_text[i],0,i,0,1);
            }
            break;
        case STATE_SHOP_MENU:
            for(int i = 0; i<30; i++){
                setRightText(shop_menu_text[i],0,i,0,1);
            }
            int foreground = 1;
            for(int i = 0; i<4; i++){
                if(game.shop_menu_index == i){
                    foreground = 2;
                }
                setRightText(shop_menu_items[i],0,(5+i*4),0,foreground);
            }
            break;
        case STATE_SHOP:
            for(int i = 0; i<30; i++){
                setRightText(shop_text[i],0,i,1,0);
            }
            for(int i = 0; i<4; i++){
                if(game.shop_index == i){
                    foreground = 2;
                }
                setRightText(shop_items[game.shop_menu_index][i],0,(5+i*4),0,foreground);
            }
            break;
        case STATE_CTRL:
            for(int i = 0; i<30; i++){
                setRightText(controls_text[i],0,i,1,0);
            }
            break;
    }
}
