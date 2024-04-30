
#include "cursor.h"

int fill_cursor(component_t filler){

    if(game.cursor_holding) return 0;
    game.cursor_height = filler.height;
    game.cursor_width = filler.width;
    for(int i = 0; i<filler.height; i++){
        for(int j = 0; j<filler.width; j++){
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
    if(game.occup_code == 0){
        game.occup_code++;
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
    block_t temp = (block_t){0};
    for(int i = 0; i<5; i++){//transpose
        for(int j = 0; j<5; j++){
            temp = game.cursor[i][j];
            game.cursor[i][j] = game.cursor[j][i];
            game.cursor[j][i] = temp;
        }
    }
    for(int i = 0; i<5; i++){//reverse rows
        for(int j = 0; j<2; j++){
            temp = game.cursor[i][j];
            game.cursor[i][j] = game.cursor[i][4-j];
            game.cursor[i][4-j] = temp;
        }
    }
    for(int i = 0; i<5; i++){
        for(int j = 0; j<5; j++){
            //cycle around the bottom 2 bits
            game.cursor[i][j].functional_index =
             (game.cursor[i][j].functional_index&0xFC)|((game.cursor[i][j].functional_index+1)&0x3);
             game.cursor[i][j].visual_index =
             (game.cursor[i][j].visual_index&0xFC)|((game.cursor[i][j].visual_index+1)&0x3);

        }
    }

}
uint8_t flood_board[50][50];

component_t cut_snapshot(int x, int y){
    if(game.occupied_board[x][y] == 0) return (component_t){0};
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
    for(int i = 0; i< 50; i++){
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
    }
    int width_start = -1;
    int width_end = -1;
    for(int i = min_y; i<min_y+5; i++){

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
    }
    /*
    xil_printf("\n%d %d\n", width_start, height_start);
    xil_printf("%d %d\n", width_end, height_end);
    xil_printf("%d %d %d", (width_start-width_end+1), ( height_start-height_end+1), toReturn.blocks[0][0].type);
    */
    toReturn.width = width_end-width_start+1;
    toReturn.height = height_end-height_start+1;
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
            }
        }
    }
    update_board(0,0,49,49);
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
