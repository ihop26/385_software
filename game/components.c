#include "components.h"

component_t shop_library [4][4];
uint32_t conveyor_library[4];
uint32_t upgrader_library[4];
uint32_t furnace_library[4];

uint16_t visual_library[4];

block_t rotate_block(block_t block){
    block_t rotated = (block_t){0};
    if(block.type == BLANK_T) return rotated;
    if(block.type == CONVEYOR_T){
        rotated.functional_index = (block.functional_index&0xFC)|((block.functional_index+1)&0x3);
        rotated.visual_index = (block.visual_index&0xFC)|((block.visual_index+1)&0x3);
    } else if(block.type == FURNACE_T){
        rotated = block;
    } else if(block.type == UPGRADER_T){
        rotated.functional_index = (block.functional_index&0xFC)|((block.functional_index+1)&0x3);
        rotated.visual_index = (block.visual_index&0xFC)|((block.visual_index+1)&0x3);
    } else if(block.type == SPAWNER_T){

    }
    return rotated;
}

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
    return 0;
}

uint32_t get_functional(block_t block){
    if(block.type == CONVEYOR_T){
        return conveyor_library[block.functional_index];

    }else if(block.type == FURNACE_T){
        return furnace_library[block.functional_index];

    }else if(block.type == UPGRADER_T){
        return upgrader_library[block.functional_index];

    }else if(block.type == SPAWNER_T){
        //return spawner_library[block.functional_index];
    	return 0;
    }else if(block.type == BLANK_T){//blank
        return 0;
    }else if(block.type == CURSOR_T){
        return 0; //cursor does nothing
    }
    return 0;
}


void initialize_shop(){
    conveyor_library[0] = 0x3005; // right
    conveyor_library[1] = 0x3881; // up
    conveyor_library[2] = 0x3045; // left
    conveyor_library[3] = 0x3081; // down

    furnace_library[0] = 0; // right
    furnace_library[1] = 0; // left
    furnace_library[2] = 0; // up 
    furnace_library[3] = 0; // down

    upgrader_library[0] = 0; // right
    upgrader_library[1] = 0; // up
    upgrader_library[2] = 0; // left
    upgrader_library[3] = 0; // down

    visual_library[0] = 0xC110; //right conveyor
    visual_library[1] = 0xC410; //up conveyor
    visual_library[2] = 0xC310; //left conveyor
    visual_library[3] = 0xC210;//down conveyor


    shop_library[0][0] = (component_t){
    	5,2,
		{
		{{CONVEYOR_T,0,0},{CONVEYOR_T,0,0},{0},{0},{0}},
		{{CONVEYOR_T,0,0},{CONVEYOR_T,0,0},{0},{0},{0}},
		{{CONVEYOR_T,0,0},{CONVEYOR_T,0,0},{0},{0},{0}},
		{{CONVEYOR_T,0,0},{CONVEYOR_T,0,0},{0},{0},{0}},
		{{CONVEYOR_T,0,0},{CONVEYOR_T,0,0},{0},{0},{0}}
		}
    };

    shop_library[0][1] = (component_t){
        	3,3,
    		{
    		{{CONVEYOR_T,3,3},{CONVEYOR_T,3,3},{CONVEYOR_T,0,0},{0},{0}},
    		{{0},{0},{CONVEYOR_T,0,0},{0},{0}},
    		{{0},{0},{CONVEYOR_T,0,0},{0},{0}},
    		{{0},{0},{0},{0},{0}},
    		{{0},{0},{0},{0},{0}}
    		}
     };
    shop_library[0][2] = (component_t){
            1,1,
        	{
        	{{CONVEYOR_T,2,2},{0},{0},{0},{0}},
        	{{0},{0},{0},{0},{0}},
        	{{0},{0},{0},{0},{0}},
        	{{0},{0},{0},{0},{0}},
        	{{0},{0},{0},{0},{0}}
        	}
     };
    shop_library[0][3] = (component_t){
           	1,1,
       		{
       		{{CONVEYOR_T,3,3},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}}
       		}
     };
}


