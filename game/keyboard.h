#ifndef __KEYB
#define __KEYB

#include "xil_types.h"
#define HOLD_THRESHOLD 13

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ESCAPE 4
#define SPACE 5
#define ENTER 6
#define R_KEY 7
#define B_KEY 8
#define C_KEY 9
#define E_KEY 10
#define Q_KEY 11

struct KEYBOARD_STATE {
	uint32_t counting[30];
	uint8_t held[30];
	uint8_t pressed[30];
};



extern struct KEYBOARD_STATE keyboard;

extern uint8_t mapper[100];

void update_keyboard_state(uint8_t buf [4]);

void setup_keyboard();

int pressed(uint8_t code);

int held(uint8_t code);

#endif
