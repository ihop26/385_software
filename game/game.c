#include "game.h"

void setup_game(){
    setup_keyboard();
    //todo make a basic startup screen
}

void handle_input(uint8_t buf [4]){
    update_keyboard_state(buf);
    //todo do stuff with the keyboard state
    if(keyboard.pressed[UP] || keyboard.held[UP]){
        keyboard.pressed[UP] = 0;
        if(game.y > -1 && game.y < 50) game.y++;
    }
    if(keyboard.pressed[DOWN] || keyboard.held[DOWN]){
        keyboard.pressed[DOWN] = 0;
        if(game.y > -1 && game.y < 50) game.y--;
    }
    if(keyboard.pressed[RIGHT] || keyboard.held[RIGHT]){
        keyboard.pressed[RIGHT] = 0;
        if(game.x > -1 && game.x < 50) game.x++;
    }
    if(keyboard.pressed[LEFT] || keyboard.held[LEFT]){
        keyboard.pressed[LEFT] = 0;
        if(game.x > -1 && game.x < 50) game.x++;
    }
}

void update_board(){
    //todo update dynamic stuff
}