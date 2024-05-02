#include "components.h"

component_t shop_library [4][8];
uint32_t conveyor_library[32];
uint32_t upgrader_library[16];
uint32_t furnace_library[4];

uint16_t visual_library[16];

block_t rotate_block(block_t block){
    block_t rotated = (block_t){0};
    rotated.type = block.type;
    if(block.type == BLANK_T) return rotated;
    if(block.type == CONVEYOR_T){
        rotated.functional_index = (block.functional_index&0xFC)|((block.functional_index+1)&0x3);
        rotated.visual_index = (block.visual_index&0xFC)|((block.visual_index+1)&0x03);
    } else if(block.type == FURNACE_T){
        rotated = block;
    } else if(block.type == UPGRADER_T){
        rotated.functional_index = (block.functional_index&0xFC)|((block.functional_index+1)&0x3);
        rotated.visual_index = (block.visual_index&0xFC)|((block.visual_index+1)&0x03);
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
    }else if(block.type == WALL_T){
        //todo return wall
        return 0x0001;
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
    }else if(block.type == WALL_T){
        return 0;
    }
    return 0;
}


void initialize_shop(){
    //fast
    conveyor_library[0] = 0x3005; // right
    conveyor_library[1] = 0x3881; // up
    conveyor_library[2] = 0x3045; // left
    conveyor_library[3] = 0x3081; // down
    //medium
    conveyor_library[4] = 0x2005; // right
    conveyor_library[5] = 0x2881; // up
    conveyor_library[6] = 0x2045; // left
    conveyor_library[7] = 0x2081; // down
    //slow
    conveyor_library[8] = 0x1005; // right
    conveyor_library[9] = 0x1881; // up
    conveyor_library[10] = 0x1045; // left
    conveyor_library[11] = 0x1081; // down
    //uber slow
    conveyor_library[12] = 0x0005; // right
    conveyor_library[13] = 0x0881; // up
    conveyor_library[14] = 0x0045; // left
    conveyor_library[15] = 0x0081; // down

    //launchers (distance 3)
    conveyor_library[16] = 0x300D; // right
    conveyor_library[17] = 0x3981; // up
    conveyor_library[18] = 0x304D; // left
    conveyor_library[19] = 0x3181; // down
    
    //todo some more furnaces?
    furnace_library[0] = 0xF0100F03; // right
    furnace_library[1] = 0; // left
    furnace_library[2] = 0; // up 
    furnace_library[3] = 0; // down

    //todo some more upgraders
    upgrader_library[0] = 0xf8110006; // right
    upgrader_library[1] = 0xf8110882; // up
    upgrader_library[2] = 0xf8110046; // left
    upgrader_library[3] = 0xf8110082; // down

    //visual stuff
    //fast
    visual_library[0] = 0xC110; //right conveyor
    visual_library[1] = 0xC410; //up conveyor
    visual_library[2] = 0xC310; //left conveyor
    visual_library[3] = 0xC210;//down conveyor
    //medium
    visual_library[4] = 0x8110; //right conveyor
    visual_library[5] = 0x8410; //up conveyor
    visual_library[6] = 0x8310; //left conveyor
    visual_library[7] = 0x8210;//down conveyor
    //slow
    visual_library[8] = 0x4110; //right conveyor
    visual_library[9] = 0x4410; //up conveyor
    visual_library[10] = 0x4310; //left conveyor
    visual_library[11] = 0x4210;//down conveyor
    //uber slow
    visual_library[12] = 0x0110; //right conveyor
    visual_library[13] = 0x0410; //up conveyor
    visual_library[14] = 0x0310; //left conveyor
    visual_library[15] = 0x0210;//down conveyor

    //slow straight
    shop_library[0][0] = (component_t){
    	3,1,
		{
		{{CONVEYOR_T,8,4},{0},{0},{0},{0}},
		{{CONVEYOR_T,8,4},{0},{0},{0},{0}},
		{{CONVEYOR_T,8,4},{0},{0},{0},{0}},
		{{0},{0},{0},{0},{0}},
		{{0},{0},{0},{0},{0}}
		}
    };
    //slow corner
    shop_library[0][1] = (component_t){
        	2,2,
    		{
    		{{CONVEYOR_T,11,7},{CONVEYOR_T,8,4},{0},{0},{0}},
    		{{0},{CONVEYOR_T,8,4},{0},{0},{0}},
    		{{0},{0},{0},{0},{0}},
    		{{0},{0},{0},{0},{0}},
    		{{0},{0},{0},{0},{0}}
    		}
     };
     //fast corner
    shop_library[0][2] = (component_t){
            4,4,
        	{
        	{{CONVEYOR_T,0,0},{0},{0},{0},{0}},
        	{{CONVEYOR_T,0,0},{0},{0},{0},{0}},
        	{{CONVEYOR_T,0,0},{0},{0},{0},{0}},
        	{{CONVEYOR_T,3,3},{CONVEYOR_T,3,3},{CONVEYOR_T,3,3},{CONVEYOR_T,3,3},{0}},
        	{{0},{0},{0},{0},{0}}
        	}
     };
     //fast straight
    shop_library[0][3] = (component_t){
           	5,3,
       		{
       		{{0},{CONVEYOR_T,0,0},{0},{0},{0}},
       		{{WALL_T,0,0},{CONVEYOR_T,0,0},{WALL_T,0,0},{0},{0}},
       		{{WALL_T,0,0},{CONVEYOR_T,0,0},{WALL_T,0,0},{0},{0}},
       		{{WALL_T,0,0},{CONVEYOR_T,0,0},{WALL_T,0,0},{0},{0}},
       		{{0},{CONVEYOR_T,0,0},{0},{0},{0}}
       		}
     };
     //launcher
     shop_library[0][4] = (component_t){
           	5,3,
       		{
       		{{WALL_T,0,0},{CONVEYOR_T,12,12},{WALL_T,0,0},{0},{0}},
       		{{WALL_T,0,0},{CONVEYOR_T,8,8},{WALL_T,0,0},{0},{0}},
       		{{WALL_T,0,0},{CONVEYOR_T,4,4},{WALL_T,0,0},{0},{0}},
       		{{WALL_T,0,0},{CONVEYOR_T,0,0},{WALL_T,0,0},{0},{0}},
       		{{WALL_T,0,0},{CONVEYOR_T,16,0},{WALL_T,0,0},{0},{0}}
       		}
     };
    //walled mini
    shop_library[0][5] = (component_t){
           	1,3,
       		{
       		{{WALL_T,0,0},{CONVEYOR_T,0,0},{WALL_T,0,0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}}
       		}
     };
    //fast mini
    shop_library[0][6] = (component_t){
           	1,1,
       		{
       		{{CONVEYOR_T,0,0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}}
       		}
     };
    //fast mini launcher
    shop_library[0][7] = (component_t){
           	1,3,
       		{
       		{{CONVEYOR_T,16,0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}}
       		}
     };


//upgraders here
    shop_library[1][0] = (component_t){
           	3,3,
       		{
       		{{CONVEYOR_T,4,0},{0},{0},{0},{0}},
       		{{UPGRADER_T,0,8},{0},{0},{0},{0}},
       		{{CONVEYOR_T,4,0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}}
       		}
     };

    shop_library[2][0] = (component_t){
           	1,1,
       		{
       		{{FURNACE_T,0,15},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}}
       		}
     };

}


