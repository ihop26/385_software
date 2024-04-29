#include "game.h"

struct GAME_INFO game;

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

    game.cursor_x = 0;
    game.cursor_y = 0;
    game.cursor_width = 0;
    game.cursor_height = 0;
    game.cursor_visual[0][0] = 0x0001;
    game.money = 0;
    game.state = 0;

    //todo set palette
    setColorPalette(0, 	0, 0, 0);
	setColorPalette(1, 0x8, 0x8, 0x8);
    setColorPalette(13, 0xF,0x6,0xF);
    setRightText("I need to make some text for this", 0, 0, 0, 1);
    setBottomText("I need to make some text for this as well", 0, 0, 0, 1);

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
    if(keyboard.pressed[UP] || keyboard.held[UP]){
        keyboard.pressed[UP] = 0;
        if(game.cursor_y > -1 && (game.cursor_y+game.cursor_height) < 49) game.cursor_y++;
    }
    if(keyboard.pressed[DOWN] || keyboard.held[DOWN]){
        keyboard.pressed[DOWN] = 0;
        if(game.cursor_y > 0 && (game.cursor_y+game.cursor_height) < 50) game.cursor_y--;
    }
    if(keyboard.pressed[RIGHT] || keyboard.held[RIGHT]){
        keyboard.pressed[RIGHT] = 0;
        if(game.cursor_x > -1 && (game.cursor_x+game.cursor_width) < 49) game.cursor_x++;
    }
    if(keyboard.pressed[LEFT] || keyboard.held[LEFT]){
        keyboard.pressed[LEFT] = 0;
        if(game.cursor_x > 0 && (game.cursor_x+game.cursor_width < 50)) game.cursor_x--;
    }
    update_visual((game.cursor_x-1),(game.cursor_y-1),(game.cursor_x+game.cursor_width),(game.cursor_y+game.cursor_height));
    //TODO UPDATE STATES ETC
}

/*
    UPDATE_VISUAL
    inputs: a rectangle of area to update
    outputs: none
    effects: rewrites the visual BRAM within the rectangle, used to selectively update the screen
*/
void update_visual(uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y){
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
