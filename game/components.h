#ifndef __COMPONENTS__
#define __COMPONENTS__


#define BLANK_T 0
#define FURNACE_T 1
#define UPGRADER_T 2
#define SPAWNER_T 3
#define CONVEYOR_T 4
#define CURSOR_T 5


#include "xil_types.h"

typedef struct
{
    uint8_t type;
    uint8_t functional_index;
    uint8_t visual_index;
}block_t;

typedef struct
{
    uint8_t width;
    uint8_t height;
    block_t blocks[5][5];

}component_t;

extern component_t shop_library [4][4];

extern uint32_t conveyor_library[16];
extern uint32_t upgrader_library[16];
extern uint32_t furnace_library[4];

extern uint16_t visual_library[16];

uint32_t get_functional(block_t block);
uint16_t get_visual(block_t block);

block_t rotate_block(block_t block);

void initialize_shop();

#endif
