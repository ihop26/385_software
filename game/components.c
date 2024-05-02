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
        return 0x0601;
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
        return 0x05AB; //grass tile?
    }else if(block.type == CURSOR_T){
        return 0; //cursor does nothing
    }else if(block.type == WALL_T){
        return 0x0620; //wall tile
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
    furnace_library[0] = 0xF0100F03; //base furnace 
    furnace_library[1] = 0xf0120003; //upgrade +50 base furnace
    furnace_library[2] = 0xf0154003; //upgrade +5 multiplier furnace  
    furnace_library[3] = 0xf0158003; //upgrade +5 exponent furnace 

	//basic +1 base upgrader
    upgrader_library[0] = 0xf8110006; // right
    upgrader_library[1] = 0xf8110882; // up
    upgrader_library[2] = 0xf8110046; // left
    upgrader_library[3] = 0xf8110082; // down
	//basic +10 upgrader
	upgrader_library[4] = 0xf05a0006; // right
    upgrader_library[5] = 0xf05a0882; // up
    upgrader_library[6] = 0xf05a0046; // left
    upgrader_library[7] = 0xf05a0082; // down
	
	//basic +1 mult upgrader (max 10)
	upgrader_library[8] = 0xf2914006; // right
    upgrader_library[9] = 0xf2914882; // up
    upgrader_library[10] = 0xf2914046; // left
    upgrader_library[11] = 0xf2914082; // down
	
	//basic +1 exp upgrader (max 2)
	upgrader_library[12] = 0xf0b18006; // right
    upgrader_library[13] = 0xf0b18882; // up
    upgrader_library[14] = 0xf0b18046; // left
    upgrader_library[15] = 0xf0b18082; // down
	

    //visual stuff
    //fast
    visual_library[0] = 0xC132; //right conveyor
    visual_library[1] = 0xC432; //up conveyor
    visual_library[2] = 0xC332; //left conveyor
    visual_library[3] = 0xC232;//down conveyor
    //medium
    visual_library[4] = 0x8132; //right conveyor
    visual_library[5] = 0x8432; //up conveyor
    visual_library[6] = 0x8332; //left conveyor
    visual_library[7] = 0x8232;//down conveyor
    //slow
    visual_library[8] = 0x4132; //right conveyor
    visual_library[9] = 0x4432; //up conveyor
    visual_library[10] = 0x4332; //left conveyor
    visual_library[11] = 0x4232;//down conveyor
    //uber slow
    visual_library[12] = 0x0132; //right conveyor
    visual_library[13] = 0x0432; //up conveyor
    visual_library[14] = 0x0332; //left conveyor
    visual_library[15] = 0x0232;//down conveyor
	//launchers
    visual_library[16] = 0xC9E2; //right launch
    visual_library[17] = 0xCCE2; //up launch
    visual_library[18] = 0xCBE2; // left launch
    visual_library[19] = 0xCAE2; // down launch

	//upgraders
	visual_library[20] = 0x4152; //right upgrader
    visual_library[21] = 0x4452; //up upgrader
    visual_library[22] = 0x4352; //left upgrader
    visual_library[23] = 0x4252;//down upgrader

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
       		{{WALL_T,0,0},{CONVEYOR_T,16,16},{WALL_T,0,0},{0},{0}}
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
       		{{CONVEYOR_T,16,16},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}}
       		}
     };


//upgraders here
    shop_library[1][0] = (component_t){
           	3,1,
       		{
       		{{CONVEYOR_T,4,4},{0},{0},{0},{0}},
       		{{UPGRADER_T,0,20},{0},{0},{0},{0}},
       		{{CONVEYOR_T,4,4},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}}
       		}
     };
	 
	 shop_library[1][1] = (component_t){
           	3,3,
       		{
       		{{CONVEYOR_T,4,4},{WALL_T,0,0},{WALL_T,0,0},{0},{0}},
       		{{CONVEYOR_T,7,7},{CONVEYOR_T,7,7},{CONVEYOR_T,4,4},{0},{0}},
       		{{WALL_T,0,0},{WALL_T,0,0},{UPGRADER_T,4,20},{0},{0}},
       		{{0},{0},{0},{0},{0}},
       		{{0},{0},{0},{0},{0}}
       		}
     };
	 
	 shop_library[1][2] = (component_t){
           	5,5,
       		{
       		{{CONVEYOR_T,4,4},{WALL_T,0,0},{WALL_T,0,0},{WALL_T,0,0},{WALL_T,0,0}},
       		{{CONVEYOR_T,7,7},{CONVEYOR_T,7,7},{CONVEYOR_T,4,4},{WALL_T,0,0},{WALL_T,0,0}},
       		{{WALL_T,0,0},{WALL_T,0,0},{UPGRADER_T,8,20},{0},{0}},
       		{{WALL_T,0,0},{WALL_T,0,0},{CONVEYOR_T,0,0},{WALL_T,0,0},{WALL_T,0,0}},
       		{{WALL_T,0,0},{WALL_T,0,0},{CONVEYOR_T,0,0},{WALL_T,0,0},{WALL_T,0,0}}
       		}
     };
	 
	 shop_library[1][3] = (component_t){
           	5,5,
       		{
       		{{WALL_T,0,0},{WALL_T,0,0},{WALL_T,0,0},{WALL_T,0,0},{WALL_T,0,0}},
       		{{WALL_T,0,0},{WALL_T,0,0},{CONVEYOR_T,0,0},{WALL_T,0,0},{WALL_T,0,0}},
       		{{WALL_T,0,0},{WALL_T,0,0},{CONVEYOR_T,0,0},{WALL_T,0,0},{WALL_T,0,0}},
       		{{WALL_T,0,0},{WALL_T,0,0},{UPGRADER_T,12,20},{WALL_T,0,0},{WALL_T,0,0}},
       		{{WALL_T,0,0},{WALL_T,0,0},{CONVEYOR_T,16,16},{WALL_T,0,0},{WALL_T,0,0}}
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
	 
	 shop_library[2][1] = (component_t){
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


