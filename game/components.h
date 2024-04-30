#ifndef __COMPONENTS
#define __COMPONENTS

#include "game.h"

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

component_t shop_library [MAX_SHOP_CATEGORIES][MAX_SHOP_ITEMS];

uint32_t conveyor_library[4];
uint32_t upgrader_library[4];
uint32_t furnace_library[4];

uint16_t visual_library[4];



void initialize_shop();

#endif