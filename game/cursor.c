
#include "cursor.h"

int fill_cursor(component_t filler){

    if(game.cursor_holding) return 0;
    game.cursor_height = filler.height;
    game.cursor_width = filler.width;
    for(int i = 0; i<filler.width; i++){
        for(int j = 0; j<filler.height; j++){
            game.cursor[i][j] = filler.blocks[i][j];
        }
    }
    if(game.cursor_x + game.cursor_width > 49){
        game.cursor_x = 49-game.cursor_width;
    }
    if(game.cursor_y + game.cursor_height > 49){
        game.cursor_y = 49-game.cursor_height;
    }
    game.cursor_holding = 1;
    update_board(0,0,49,49);

    return 1;
}

int place_cursor(){

    if(!game.cursor_holding) return 0;

    uint8_t x = game.cursor_x;
    uint8_t y = game.cursor_y;

    for(int i = 0; i<game.cursor_width; i++){
        for(int j = 0; j<game.cursor_height;j++){
            if(game.occupied_board[x+i][y+j] != 0 && game.cursor[i][j].type != BLANK_T) return 0;
        }
    }
    for(int i = 0; i<game.cursor_width; i++){
        for(int j = 0; j<game.cursor_height;j++){
            if(game.cursor[i][j].type != BLANK_T){
                game.board[x+i][y+j] = game.cursor[i][j];
                game.occupied_board[x+i][y+j] = game.occup_code;
            }
        }
    }
    game.occup_code++;
    if(game.occup_code == 0 || game.occup_code == 1){
        game.occup_code = 2;
    }
    update_board(0,0,49,49);
    return 1;
}
int dump_cursor(){
    for(int i = 0; i<5; i++){
        for(int j = 0; j<5; j++){
            game.cursor[i][j] = (block_t){0};
        }
    }
    game.cursor[0][0] = (block_t){5,0,0};
    game.cursor_holding = 0;
    game.cursor_height = 1;
    game.cursor_width = 1;
    update_board(0,0,49,49);
    return 1;
}
int rotate_cursor(){
    component_t rotated = (component_t){0};
    rotated.width = game.cursor_height;
    rotated.height = game.cursor_width;
    for(int i = 0; i<game.cursor_width; i++){//transpose
    	for(int j = 0; j<game.cursor_height; j++){
    		rotated.blocks[j][i] = game.cursor[i][j];
    	}
    }
    block_t temp = (block_t){0};
    for(int i = 0; i<rotated.width; i++){
    	for(int j = 0; j<rotated.height/2; j++){
    		temp = rotated.blocks[i][j];
    		    		rotated.blocks[i][j] = rotated.blocks[i][rotated.height-j-1];
    		    		rotated.blocks[i][rotated.height-j-1] = temp;
    	}
    }

    for(int i = 0; i<rotated.width; i++){
        for(int j = 0; j<rotated.height; j++){
            rotated.blocks[i][j] = rotate_block(rotated.blocks[i][j]);
        }
    }
    dump_cursor();
    fill_cursor(rotated);
    for(int i = 0; i< 5; i++){
    	for(int j = 0; j<5; j++){
    		xil_printf("%d ",game.cursor[i][j].type);
    	}
    	xil_printf("\n");
    }
    return 1;
}
uint8_t flood_board[50][50];

component_t cut_snapshot(int x, int y){
    if(game.occupied_board[x][y] == 0 || game.occupied_board[x][y] == 1) return (component_t){0};
    int key = game.occupied_board[x][y];
    for(int i = 0; i<50; i++){
    	for(int j = 0; j<50; j++){
    		flood_board[i][j] = 0;
    	}
    }
    flood_select(x, y, key); //grab component and put it into snapshot
    component_t toReturn;
    //time to copy things into the cursor
    int min_x = 51;
    int min_y = 51;
    int height_start = -1;
    int height_end = -1;
    int max_width = 0;
    int max_height = 0;
    for(int i = 0; i< 50; i++){
    	height_start = -1;
    	height_end = -1;
        for(int j = 0; j<50; j++){
            if(game.snapshot[i][j].type != BLANK_T){
                if(i < min_x){
                    min_x = i;
                }
                if(j < min_y){
                    min_y = j;
                }
                if(height_start == -1){
                    height_start = j;
                    height_end = j;
                }else{
                	height_end = j;
                }
            }
        }
        if(height_end-height_start+1 > max_height){
        	max_height = height_end-height_start+1;
        }
    }
    xil_printf("\nx:%d y:%d", min_x, min_y);
    int width_start = -1;
    int width_end = -1;
    for(int i = min_y; i<min_y+5; i++){
    	width_end = -1;
    	width_start = -1;
        for(int j = min_x; j<min_x+5; j++){
            toReturn.blocks[j-min_x][i-min_y] = game.snapshot[j][i];
            if(game.snapshot[j][i].type != BLANK_T){
            	if(width_start == -1){
            		width_start = j;
            		width_end = j;
            	}else{
            		width_end = j;
            	}
            }
        }
        if(width_end-width_start+1 > max_width){
        	max_width = width_end-width_start+1;
        }
    }

    toReturn.height = max_height;
    toReturn.width = max_width;
    xil_printf("\n%d %d %d", toReturn.width,toReturn.height,toReturn.blocks[1][0].type);
    update_board(0,0,49,49);
    return toReturn;
}

int flood_select(int x, int y, int key){
    if(x < 0 || x > 49 || y < 0 || y > 49) return -1;
    if(flood_board[x][y] == 1) return -1;
    flood_board[x][y] = 1;
    if(game.occupied_board[x][y] == key){//take the board data into snapshot
        game.snapshot[x][y] = game.board[x][y];
        game.board[x][y] = (block_t){0};
        game.occupied_board[x][y] = 0;
    }else{
    	return -1;
    }
    flood_select(x-1,y,key);
    flood_select(x+1,y,key);
    flood_select(x,y-1,key);
    flood_select(x,y+1,key);
    return 1;
}

int paste_snapshot(){
    int changed = 0;
    for(int i = 0; i<50; i++){
        for(int j = 0; j< 50; j++){
            if(game.snapshot[i][j].type != BLANK_T){
                changed = 1;
                game.board[i][j] = game.snapshot[i][j];
                game.occupied_board[i][j] = game.occup_code;
            }
        }
    }
    game.occup_code++;
    if(changed) update_board(0,0,49,49);
    return changed;
}

int clear_snapshot(){
    for(int i = 0; i<50; i++){
        for(int j = 0; j< 50; j++){
            game.snapshot[i][j] = (block_t){0};
        }
    }

    return 1;
}
