

/***************************** Include Files *******************************/
#include "hdmi_text_controller.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sleep.h"

/************************** Function Definitions ***************************/

#define con_right 0x2005
#define con_down 0x2081

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

void textHDMIColorClr()
{
	for (int i = 0; i<(ROWS*COLUMNS) * 2; i++)
	{
		hdmi_ctrl->TEXT[i] = 0x00;
	}
}

void textHDMIDrawColorText(char* str, int x, int y, uint8_t background, uint8_t foreground)
{
	int i = 0;
	while (str[i]!=0)
	{
		hdmi_ctrl->TEXT[(y*COLUMNS + x + i) * 2] = foreground << 4 | background;
		hdmi_ctrl->TEXT[(y*COLUMNS + x + i) * 2 + 1] = str[i];
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


void hdmiTest()
{
    //On-chip memory write and readback test
	paletteTest();
}

