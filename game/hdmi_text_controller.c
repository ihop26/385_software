

/***************************** Include Files *******************************/
#include "hdmi_text_controller.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sleep.h"

/************************** Function Definitions ***************************/

void rightTextClr()
{
	for (int i = 0; i<(RIGHT_ROWS*RIGHT_COLUMNS) * 2; i++)
	{
		hdmi_ctrl->TEXT[i] = 0x00;
	}
}

void bottomTextClr()
{
	for (int i = 0; i<(BOTTOM_ROWS*BOTTOM_COLUMNS) * 2; i++)
	{
		hdmi_ctrl->BOTTOM_BAR[i] = 0x00;
	}
}

void setRightText(char* str, int x, int y, uint8_t background, uint8_t foreground)
{
	int i = 0;
	while (str[i]!=0)
	{
		hdmi_ctrl->TEXT[(y*RIGHT_COLUMNS + x + i) * 2] = foreground << 4 | background;
		hdmi_ctrl->TEXT[(y*RIGHT_COLUMNS + x + i) * 2 + 1] = str[i];
		i++;
	}
}
void setBottomText(char* str, int x, int y, uint8_t background, uint8_t foreground)
{
	int i = 0;
	while (str[i]!=0)
	{
		hdmi_ctrl->BOTTOM_BAR[(y*(BOTTOM_COLUMNS+30) + x + i) * 2] = foreground << 4 | background;
		hdmi_ctrl->BOTTOM_BAR[(y*(BOTTOM_COLUMNS+30) + x + i) * 2 + 1] = str[i];
		i++;
	}
}

void setColorPalette (uint8_t color, uint8_t red, uint8_t green, uint8_t blue)
{
	//fill in this function to set the color palette starting at offset 0x0000 2000 (from base)
	hdmi_ctrl->PALETTE[color*4] = red;
	hdmi_ctrl->PALETTE[color*4+1] = green;
	hdmi_ctrl->PALETTE[color*4+2] = blue;
	printf ("set %d to %d,\n\r",color,((red<<8)+(green<<4)+(blue)));
}

void setVisual(uint16_t code, int x, int y){
	hdmi_ctrl->VISUAL[x*2+y*100] = (code & 0xFF);
	hdmi_ctrl->VISUAL[x*2+y*100+1] = ((code>>8) & 0xFF);
}

void setBoard(uint32_t code, int x, int y){
	hdmi_ctrl->BOARD[x*4+y*200] = (code & 0xFF);
	hdmi_ctrl->BOARD[x*4+y*200+1] = ((code >> 8) & 0xFF);
	hdmi_ctrl->BOARD[x*4+y*200+2] = ((code >> 16) & 0xFF);
	hdmi_ctrl->BOARD[x*4+y*200+3] = ((code >> 24) & 0xFF);
}

void setMine(uint8_t index, uint64_t code){
	hdmi_ctrl->SPAWNERS[0+8*index] = ((code >>  0) & 0xFF);
	hdmi_ctrl->SPAWNERS[1+8*index] = ((code >>  8) & 0xFF);
	hdmi_ctrl->SPAWNERS[2+8*index] = ((code >> 16) & 0xFF);
	hdmi_ctrl->SPAWNERS[3+8*index] = ((code >> 24) & 0xFF);
	hdmi_ctrl->SPAWNERS[4+8*index] = ((code >> 32) & 0xFF);
	hdmi_ctrl->SPAWNERS[5+8*index] = ((code >> 40) & 0xFF);
	hdmi_ctrl->SPAWNERS[6+8*index] = ((code >> 48) & 0xFF);
	hdmi_ctrl->SPAWNERS[7+8*index] = ((code >> 56) & 0xFF);
}

int getOre(int index, uint8_t* bytes){
	int changed = 0;
	int starting = 8*index;
	for(int x = 0; x<8; x++){
		bytes[x] = 	hdmi_ctrl->SELL[starting+x];
		if(bytes[x] != 0) changed = 1;
		hdmi_ctrl->SELL[starting+x] = 0;
	}
	return changed;
}


//////////////////////////////////////////////////////////////////////////////////
/*                                    UNUSED                                    */
//////////////////////////////////////////////////////////////////////////////////
/*
void paletteTest()
{
	textHDMIColorClr();

	setColorPalette(0, 	0, 0, 0);
	setColorPalette(1, 0x8, 0x8, 0x8);
	setColorPalette(2, 0x4, 0x4, 0x4);
	setColorPalette(3,0x0,0x0,0x8);
	setColorPalette(4,0x0,0x8,0x0);
	setColorPalette(5,0x8,0x0,0x0);
	setColorPalette(13, 0xF,0x6,0xF);

	textHDMIDrawColorText("hello world!",0,0,0,1);

		hdmi_ctrl->BOTTOM_BAR[0] = 0x10;
		hdmi_ctrl->BOTTOM_BAR[1] = 'h';



	int starting = 0;
	int i = 0;
	hdmi_ctrl->SPAWNERS[starting +8*i] = 0x40;
	hdmi_ctrl->SPAWNERS[starting+1+8*i] = 0x10;
	hdmi_ctrl->SPAWNERS[starting+2+8*i] = 0x00;
	hdmi_ctrl->SPAWNERS[starting+3+8*i] = 0x00;
	hdmi_ctrl->SPAWNERS[starting+4+8*i] = 0x01;
	hdmi_ctrl->SPAWNERS[starting+5+8*i] = 0x80;
	hdmi_ctrl->SPAWNERS[starting+6+8*i] = 0x01;
	hdmi_ctrl->SPAWNERS[starting+7+8*i] = 0x00;

	i = i+1;
	hdmi_ctrl->SPAWNERS[starting +8*i] = 0x80;
	hdmi_ctrl->SPAWNERS[starting+1+8*i] = 0x10;
	hdmi_ctrl->SPAWNERS[starting+2+8*i] = 0x00;
	hdmi_ctrl->SPAWNERS[starting+3+8*i] = 0x00;
	hdmi_ctrl->SPAWNERS[starting+4+8*i] = 0x01;
	hdmi_ctrl->SPAWNERS[starting+5+8*i] = 0x80;
	hdmi_ctrl->SPAWNERS[starting+6+8*i] = 0x01;
	hdmi_ctrl->SPAWNERS[starting+7+8*i] = 0x00;

	int max = 49;
	for(int i = 0; i<=max; i++){
		for(int j = 0; j<=max; j++){
			if(j>i)break;
			if(i == 49 && j == 49){
				hdmi_ctrl->BOARD[j*4+i*200] = 0x03;
				hdmi_ctrl->BOARD[j*4+i*200+1] = 0x0F;
				hdmi_ctrl->BOARD[j*4+i*200+2] = 0x10;
				hdmi_ctrl->BOARD[j*4+i*200+3] = 0xF0;
				hdmi_ctrl->VISUAL[j*2+i*100] = 0x11;
				hdmi_ctrl->VISUAL[j*2+i*100+1] = 0xC0;
			}else if(i==j){
				hdmi_ctrl->BOARD[j*4+i*200] = 0x81;
				hdmi_ctrl->BOARD[j*4+i*200+1] = 0x30;
				hdmi_ctrl->VISUAL[j*2+i*100] = 0x20;
				hdmi_ctrl->VISUAL[j*2+i*100+1] = 0xC2;
			}else {
				hdmi_ctrl->BOARD[j*4+i*200] = 0x05;
				hdmi_ctrl->BOARD[j*4+i*200+1] = 0x30;
				hdmi_ctrl->VISUAL[j*2+i*100] = 0x20;
				hdmi_ctrl->VISUAL[j*2+i*100+1] = 0xC1;
			}


		}
	}



}
*/
