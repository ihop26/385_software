#include "keyboard.h"

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
	mapper[0x52] = 0;//up arrow
	mapper[0x51] = 1;//down arrow
	mapper[0x50] = 2;//left arrow
	mapper[0x4F] = 3;//right arrow
	mapper[0x29] = 4;//escape
	mapper[0x2c] = 5;//spacebar
	mapper[0x28] = 6;//enter
	mapper[0x15] = 7;//r
}

