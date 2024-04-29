#ifndef HDMI_TEXT_CONTROLLER_H
#define HDMI_TEXT_CONTROLLER_H


/****************** Include Files ********************/
#include "xil_types.h"
#include "xstatus.h"
#include "xparameters.h"

#define RIGHT_COLUMNS 30
#define BOTTOM_COLUMNS 50
#define RIGHT_ROWS 25
#define BOTTOM_ROWS 5
#define MAX_ORES 256
#define MAX_SPAWNERS 64
#define PALETTE_START 0x0000
#define TEXT_START 0x8000
#define BOTTOM_BAR_START 0x8800
#define BOARD_START 0x10000
#define SELL_START 0x13000
#define SPAWNER_START 0x13800
#define VISUAL_START 0x18000
#define COLORS 16
#define GRID_SIZE 50

#define PALETTE_SIZE COLORS*4
#define TEXT_SIZE RIGHT_ROWS*RIGHT_COLUMNS*2

#define BOTTOM_BAR_SIZE BOTTOM_ROWS*BOTTOM_COLUMNS*2
#define BOARD_SIZE GRID_SIZE*GRID_SIZE*4
#define VISUAL_SIZE GRID_SIZE*GRID_SIZE*2
#define SELL_SIZE MAX_ORES*8
#define SPAWNER_SIZE MAX_SPAWNERS*8

struct TEXT_HDMI_STRUCT {
	uint8_t				PALETTE[PALETTE_SIZE];//4 = r,g,b,space
	uint8_t				PAD1[TEXT_START-(PALETTE_SIZE+PALETTE_START)];
	uint8_t		      	TEXT [TEXT_SIZE];
	uint8_t				PAD2 [BOTTOM_BAR_START - (TEXT_SIZE+TEXT_START)];
	uint8_t				BOTTOM_BAR [BOTTOM_BAR_SIZE];
	uint8_t				PAD3[BOARD_START-(BOTTOM_BAR_START+BOTTOM_BAR_SIZE)];
	uint8_t				BOARD [BOARD_SIZE];
	uint8_t				PAD4[SELL_START-(BOARD_SIZE+BOARD_START)];
	uint8_t				SELL[SELL_SIZE];
	uint8_t				PAD5[SPAWNER_START-(SELL_START+SELL_SIZE)];
	uint8_t				SPAWNERS[SPAWNER_SIZE];
	uint8_t				PAD6[VISUAL_START-(SPAWNER_START+SPAWNER_SIZE)];
	uint8_t				VISUAL[VISUAL_SIZE];
};

//you may have to change this line depending on your platform designer
static volatile struct TEXT_HDMI_STRUCT* hdmi_ctrl = XPAR_HDMI_TEXT_CONTROLLER_0_AXI_BASEADDR;

/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a HDMI_TEXT_CONTROLLER register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the HDMI_TEXT_CONTROLLERdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void HDMI_TEXT_CONTROLLER_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
#define HDMI_TEXT_CONTROLLER_mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/**
 *
 * Read a value from a HDMI_TEXT_CONTROLLER register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the HDMI_TEXT_CONTROLLER device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 HDMI_TEXT_CONTROLLER_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define HDMI_TEXT_CONTROLLER_mReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))

/************************** Function Prototypes ****************************/
/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the HDMI_TEXT_CONTROLLER instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */

void rightTextClr();
void bottomTextClr();
void setRightText(char* str, int x, int y, uint8_t background, uint8_t foreground);
void setBottomText(char* str, int x, int y, uint8_t background, uint8_t foreground);
void setColorPalette (uint8_t color, uint8_t red, uint8_t green, uint8_t blue); //Fill in this code
void setVisual(uint16_t code, int x, int y);
void setBoard(uint32_t code, int x, int y);
void setMine(uint8_t index, uint64_t ore);

#endif // HDMI_TEXT_CONTROLLER_H
