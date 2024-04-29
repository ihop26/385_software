#include "keyboard.h"

struct KEYBOARD_STATE keyboard;
uint8_t mapper[100];

void update_keyboard_state(uint8_t buf [4]){

	uint8_t keyb_index;
	uint8_t still_pressed [30];
	for(int i = 0; i<30; i++){
		still_pressed[i] = 0;
	}

	for(int i = 0; i < 4; i++){ //get correct indexing & figure out which buttons are pressed rn
		keyb_index = mapper[buf[i]];
		if(keyb_index > 29) continue;
		keyboard.counting[keyb_index]++;
		still_pressed[keyb_index]++;
	}

	for(int i = 0; i<30; i++){
		if(!still_pressed[i]){//let go/never pressed
			if(keyboard.counting[i]>0 && keyboard.held[i]==0){//if it was just pressed
				keyboard.pressed[i] = 1;
			}
			keyboard.counting[i] = 0;//reset counting/hold since it isn't still being pressed
			keyboard.held[i] = 0;
		}else{//this button is being pressed
			keyboard.counting[i]++;
			if(keyboard.counting[i] > HOLD_THRESHOLD){//press long enough -> hold
				keyboard.held[i] = 1;
			}
		}
	}
}

void setup_keyboard(){
	for(int i = 0; i<30; i++){
		keyboard.counting[i] = 0;
		keyboard.pressed[i] = 0;
		keyboard.held[i] = 0;
	}
	for(int i = 0; i<100; i++){
		mapper[i] = 30;
	}
	mapper[0x52] = UP;
	mapper[0x51] = DOWN;
	mapper[0x50] = LEFT;
	mapper[0x4F] = RIGHT;
	mapper[0x29] = ESCAPE;
	mapper[0x2c] = SPACE;
	mapper[0x28] = ENTER;
	mapper[0x15] = R_KEY;
	mapper[0x05] = B_KEY;
	mapper[0x06] = C_KEY;
	mapper[0x08] = E_KEY;
	mapper[0x14] = Q_KEY;
	mapper[0x16] = S_KEY;
	mapper[0x1A] = W_KEY;

}

int pressed(uint8_t code){
	if(keyboard.pressed[code]){
		keyboard.pressed[code] = 0;
		return 1;
	}
	return 0;
}

int held(uint8_t code){
	return keyboard.held[code];
}
