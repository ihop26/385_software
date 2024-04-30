#include "components.h"


#define BLANK_T 0
#define FURNACE_T 1
#define UPGRADER_T 2
#define SPAWNER_T 3
#define CONVEYOR_T 4
#define CURSOR_T 5

uint16_t get_visual(block_t block){
    if(block.type == CONVEYOR_T){
        return visual_library[block.visual_index];

    }else if(block.type == FURNACE_T){
        return visual_library[block.visual_index];

    }else if(block.type == UPGRADER_T){
        return visual_library[block.visual_index];

    }else if(block.type == SPAWNER_T){
        return visual_library[block.visual_index];

    }else if(block.type == BLANK_T){//blank
        return 0;
    }else if(block.type == CURSOR_T){
        return 0x0001; //blank cursor
    }
}

uint32_t get_functional(){
    if(block.type == CONVEYOR_T){
        return conveyor_library[block.functional_index];

    }else if(block.type == FURNACE_T){
        return furnace_library[block.functional_index];

    }else if(block.type == UPGRADER_T){
        return upgrader_library[block.functional_index];

    }else if(block.type == SPAWNER_T){
        return spawner_library[block.functional_index];

    }else if(block.type == BLANK_T){//blank
        return 0;
    }else if(block.type == CURSOR_T){
        return 0; //cursor does nothing
    }
}


void initialize_shop(){
    conveyor_library[0] = 0x3005; // right
    conveyor_library[1] = 0x3041; // left
    conveyor_library[2] = 0x3881; // up 
    conveyor_library[3] = 0x3081; // down

    furnace_library[0] = 0; // right
    furnace_library[1] = 0; // left
    furnace_library[2] = 0; // up 
    furnace_library[3] = 0; // down

    upgrader_library[0] = 0; // right
    upgrader_library[1] = 0; // left
    upgrader_library[2] = 0; // up 
    upgrader_library[3] = 0; // down

    visual_library[0] = 0xC120; //right conveyor
    visual_library[1] = 0xC320; //left conveyor
    visual_library[2] = 0xC420; //up conveyor
    visual_library[3] = 0xC220;//down conveyor


    shop_library[0][0].width = 1;
    shop_library[0][0].height = 1;
    shop_library[0][0].blocks = {
        {{CONVEYOR_T,0,0},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}}
        };
    shop_library[0][1].width = 1;
    shop_library[0][1].height = 1;
    shop_library[0][1].blocks = {
        {{CONVEYOR_T,1,1},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}}
        };
    shop_library[0][2].width = 1;
    shop_library[0][2].height = 1;
    shop_library[0][2].blocks = {
        {{CONVEYOR_T,2,2},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}}
        };
    shop_library[0][3].width = 1;
    shop_library[0][3].height = 1;
    shop_library[0][3].blocks = {
        {{CONVEYOR_T,3,3},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}},
        {{0},{0},{0},{0},{0}},
        };
}