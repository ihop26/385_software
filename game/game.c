#include "game.h"

struct GAME_INFO game;

/////////////////////////////////////////////////////////////
/*         TODO LIST                                       */
/*       1. add states to the game      DONE               */
/*       2. add simple shop functionality   DONE           */
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
    uint64_t initial_mine = 0x0001800100001040;
    setMine(0,initial_mine);
    game.buying = 0;
    game.cursor_holding = 0;
    game.occup_code = 1;
    game.cursor_x = 0;
    game.cursor_y = 0;
    game.cursor_width = 1;
    game.cursor_height = 1;
    game.cursor[0][0] = (block_t){5,0,0};
    game.money = 0;
    game.state = STATE_MENU;
    game.shop_index = 0;
    game.shop_menu_index = 0;
    //todo set palette
    setColorPalette(0, 	0, 0, 0);
	setColorPalette(1, 0x8, 0x8, 0x8);
    setColorPalette(2, 0x0, 0x8, 0x0);
    setColorPalette(13, 0xF,0x6,0xF);



    setColorPalette(14, 0x8, 0x0, 0x0);
    setColorPalette(15, 0x0, 0x8, 0x0);



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

    if(pressed(UP) || held(UP)){
        if(game.cursor_y > 0 && (game.cursor_y+game.cursor_height-1) < 50) game.cursor_y--;
    }
    if(pressed(DOWN) || held(DOWN)){
        if(game.cursor_y > -1 && (game.cursor_y+game.cursor_height-1) < 49) game.cursor_y++;
    }
    if(pressed(RIGHT) || held(RIGHT)){
        if(game.cursor_x > -1 && (game.cursor_x+game.cursor_width-1) < 49) game.cursor_x++;
    }
    if(pressed(LEFT) || held(LEFT)){
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
    
    if(pressed_esc && game.cursor_holding){//dump whatever you have
        pressed_esc = 0; //use up action if holding
        if(!game.buying){
            paste_snapshot();
            clear_snapshot();
        }
    	dump_cursor();
    }
        
    
    switch(game.state){
        case STATE_MENU:
            game.cursor_locked = TRUE;
            if(pressed(B_KEY)){
                right_bar_changed = 1;
                game.state = STATE_SHOP_MENU;
            } else if(pressed(C_KEY)){
                right_bar_changed = 1;
                game.state = STATE_CTRL;
            } 
            break;
        case STATE_SHOP_MENU: //shop menu has 4 categories: conveyors, mines, upgraders, furnaces
            game.cursor_locked = FALSE;
            game.shop_index = 0;
            if(pressed_esc){
                right_bar_changed = 1;
                game.state = STATE_MENU;
            } else if(pressed(W_KEY)){
                right_bar_changed = 1;
                game.shop_menu_index = ((game.shop_menu_index-1)+MAX_SHOP_CATEGORIES)%MAX_SHOP_CATEGORIES;
            } else if(pressed(S_KEY)){
                right_bar_changed = 1;
                game.shop_menu_index = ((game.shop_menu_index+1)+MAX_SHOP_CATEGORIES)%MAX_SHOP_CATEGORIES;
            } else if(pressed(B_KEY)){
                right_bar_changed = 1;
                game.state = STATE_SHOP;
            }
            break;  
        case STATE_SHOP: //shop menu for individual categories, index through
            game.cursor_locked = FALSE;
            if(pressed_esc){
                right_bar_changed = 1;
                game.state = STATE_SHOP_MENU;
            }else if(pressed(W_KEY)){
                right_bar_changed = 1;
                game.shop_index = ((game.shop_index-1)+MAX_SHOP_ITEMS)%MAX_SHOP_ITEMS;
            }else if(pressed(S_KEY)){
                right_bar_changed = 1;
                game.shop_index = ((game.shop_index+1)+MAX_SHOP_ITEMS)%MAX_SHOP_ITEMS;
            }else if(pressed(B_KEY)){
                if(!game.cursor_holding){
                    game.buying = 1;
                    fill_cursor(shop_library[game.shop_menu_index][game.shop_index]);
                }
            } 
            break;
        case STATE_CTRL:
            game.cursor_locked = TRUE;
            if(pressed(ESCAPE)){
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
            break;
        case STATE_SHOP_MENU:
            for(int i = 0; i<30; i++){
                setRightText(shop_menu_text[i],0,i,0,1);
            }
            for(int i = 0; i<4; i++){
                foreground = 1;
                if(game.shop_menu_index == i){
                    foreground = 2;
                }
                setRightText(shop_menu_items[i],0,(5+i*4),0,foreground);
            }
            break;
        case STATE_SHOP:
            for(int i = 0; i<30; i++){
                setRightText(shop_text[i],0,i,0,1);
            }
            for(int i = 0; i<4; i++){
                foreground = 1;
                if(game.shop_index == i){
                    foreground = 2;
                }
                setRightText(shop_items[game.shop_menu_index][i],0,(5+i*4),0,foreground);
            }
            break;
        case STATE_CTRL:
            for(int i = 0; i<30; i++){
                setRightText(controls_text[i],0,i,0,1);
            }
            break;
    }
}

int fill_cursor(component_t filler){

    if(game.cursor_holding) return 0;
    game.cursor_height = filler.height;
    game.cursor_width = filler.width;
    for(int i = 0; i<filler.height; i++){
        for(int j = 0; j<filler.width; j++){
            game.cursor[i][j] = filler.blocks[i][j];
        }
    }
    if(game.cursor_x + game.cursor_width > 49){
        game.cursor_x = 49-game.cursor_width;
    }
    if(game.cursor_y + game.cursor_height > 49){
        game.cursor_y = 49-game.cursor_height;
    }
    game.cursor_holding = 1;
    update_board(0,0,49,49);

    return 1;
}

int place_cursor(){

    if(!game.cursor_holding) return 0;

    uint8_t x = game.cursor_x;
    uint8_t y = game.cursor_y;

    for(int i = 0; i<game.cursor_width; i++){
        for(int j = 0; j<game.cursor_height;j++){
            if(game.occupied_board[x+i][y+j] != 0 && game.cursor[i][j].type != BLANK_T) return 0;
        }
    }
    for(int i = 0; i<game.cursor_width; i++){
        for(int j = 0; j<game.cursor_height;j++){
            if(game.cursor[i][j].type != BLANK_T){
                game.board[x+i][y+j] = game.cursor[i][j];
                game.occupied_board[x+i][y+j] = game.occup_code;
            }
        }
    }
    game.occup_code++;
    if(game.occup_code == 0){
        game.occup_code++;
    }
    update_board(0,0,49,49);
    return 1;
}
int dump_cursor(){
    for(int i = 0; i<5; i++){
        for(int j = 0; j<5; j++){
            game.cursor[i][j] = (block_t){0};
        }
    }
    game.cursor[0][0] = (block_t){5,0,0};
    game.cursor_holding = 0;
    game.cursor_height = 1;
    game.cursor_width = 1;
    update_board(0,0,49,49);
    return 1;
}

uint8_t flood_board[50][50];

component_t cut_snapshot(int x, int y){
    if(game.occupied_board[x][y] == 0) return (component_t){0};
    int key = game.occupied_board[x][y];
    for(int i = 0; i<50; i++){
    	for(int j = 0; j<50; j++){
    		flood_board[i][j] = 0;
    	}
    }
    flood_select(x, y, key); //grab component and put it into snapshot
    component_t toReturn;
    //time to copy things into the cursor
    int min_x = 51;
    int min_y = 51;

    for(int i = 0; i< 50; i++){
        int height_start = -1;
        int height_end = -1;
        for(int j = 0; j<50; j++){
            if(game.snapshot[i][j].type != BLANK_T){
                if(i < min_x){
                    min_x = i;
                }
                if(j < min_y){
                    min_y = j;
                }
                if(width_start == -1){
                    height_start = j;
                    height_end = j;
                }else{
                	height_end = j;
                }
            }
        }
    }
    
    for(int i = min_y; i<min_y+5; i++){
        int width_start = -1;
        int width_end = -1;
        for(int j = min_x; j<min_x+5; j++){
            toReturn.blocks[j-min_x][i-min_y] = game.snapshot[j][i];
            if(game.snapshot[j][i].type != BLANK_T){
            	if(width_start == -1){
            		width_start = j;
            		width_end = j;
            	}else{
            		width_end = j;
            	}
            }
        }
    }
    toReturn.width = width_start-width_end+1;
    toReturn.height = height_start-height_end+1;
    update_board(0,0,49,49);
    return toReturn;
}

int flood_select(int x, int y, int key){
    if(x < 0 || x > 49 || y < 0 || y > 49) return -1;
    if(flood_board[x][y] == 1) return -1;
    flood_board[x][y] = 1;
    if(game.occupied_board[x][y] == key){//take the board data into snapshot
        game.snapshot[x][y] = game.board[x][y];
        game.board[x][y] = (block_t){0};
        game.occupied_board[x][y] = 0;
    }else{
    	return -1;
    }
    flood_select(x-1,y,key);
    flood_select(x+1,y,key);
    flood_select(x,y-1,key);
    flood_select(x,y+1,key);
    return 1;
}

int paste_snapshot(){
    int changed = 0;
    for(int i = 0; i<50; i++){
        for(int j = 0; j< 50; j++){
            if(game.snapshot[i][j].type != BLANK_T){
                changed = 1;
                game.board[i][j] = game.snapshot[i][j];
            }
        }
    }
    update_board(0,0,49,49);
    return changed;
}

int clear_snapshot(){
    for(int i = 0; i<50; i++){
        for(int j = 0; j< 50; j++){
            game.snapshot[i][j] = (block_t){0};
        }
    }

    return 1;
}
