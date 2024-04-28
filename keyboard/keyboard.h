#ifndef __KEYB
#define __KEYB

#include "xil_types.h"
#define HOLD_THRESHOLD 5

struct KEYBOARD_STATE {
	uint32_t counting[30];
	uint8_t held[30];
	uint8_t pressed[30];
};



static struct KEYBOARD_STATE keyboard;
static uint8_t mapper[100];

void update_keyboard_state(uint8_t buf [4]);

void setup_keyboard();


#endif
