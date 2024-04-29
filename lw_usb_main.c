#include <stdio.h>
#include "platform.h"
#include "lw_usb/GenericMacros.h"
#include "lw_usb/GenericTypeDefs.h"
#include "lw_usb/MAX3421E.h"
#include "lw_usb/USB.h"
#include "lw_usb/usb_ch9.h"
#include "lw_usb/transfer.h"
#include "lw_usb/HID.h"


#include "game/game.h"

#include "xparameters.h"
#include <xgpio.h>

extern HID_DEVICE hid_device;

static XGpio Gpio_hex;

static BYTE addr = 1; 				//hard-wired USB address
const char* const devclasses[] = { " Uninitialized", " HID Keyboard", " HID Mouse", " Mass storage" };


static BYTE rcode;
static BOOT_MOUSE_REPORT buf;		//USB mouse report
static BOOT_KBD_REPORT kbdbuf;
static BYTE runningdebugflag = 0;//flag to dump out a bunch of information when we first get to USB_STATE_RUNNING
static BYTE errorflag = 0; //flag once we get an error device so we don't keep dumping out state info
static BYTE device;


BYTE GetDriverandReport() {
	BYTE i;
	BYTE rcode;
	BYTE device = 0xFF;
	BYTE tmpbyte;

	DEV_RECORD* tpl_ptr;
	xil_printf("Reached USB_STATE_RUNNING (0x40)\n");
	for (i = 1; i < USB_NUMDEVICES; i++) {
		tpl_ptr = GetDevtable(i);
		if (tpl_ptr->epinfo != NULL) {
			xil_printf("Device: %d", i);
			xil_printf("%s \n", devclasses[tpl_ptr->devclass]);
			device = tpl_ptr->devclass;
		}
	}
	//Query rate and protocol
	rcode = XferGetIdle(addr, 0, hid_device.interface, 0, &tmpbyte);
	if (rcode) {   //error handling
		xil_printf("GetIdle Error. Error code: ");
		xil_printf("%x \n", rcode);
	} else {
		xil_printf("Update rate: ");
		xil_printf("%x \n", tmpbyte);
	}
	xil_printf("Protocol: ");
	rcode = XferGetProto(addr, 0, hid_device.interface, &tmpbyte);
	if (rcode) {   //error handling
		xil_printf("GetProto Error. Error code ");
		xil_printf("%x \n", rcode);
	} else {
		xil_printf("%d \n", tmpbyte);
	}
	return device;
}

void printHex (u32 data, unsigned channel)
{
	XGpio_DiscreteWrite (&Gpio_hex, channel, data);
}

void get_input()
{
	xil_printf("."); //A tick here means one loop through the USB main handler
	MAX3421E_Task();
	USB_Task();
	if (GetUsbTaskState() == USB_STATE_RUNNING) {
		if (!runningdebugflag) {
			runningdebugflag = 1;
			device = GetDriverandReport();
		} else if (device == 1) {
			//run keyboard debug polling
			rcode = kbdPoll(&kbdbuf);
			if (rcode == hrNAK) {
					return; //NAK means no new data
				} else if (rcode) {
					xil_printf("Rcode: ");
					xil_printf("%x \n", rcode);
					return;
				}
				xil_printf("keycodes: ");
				for (int i = 0; i < 6; i++) {
					xil_printf("%x ", kbdbuf.keycode[i]);
				}
				//Outputs the first 4 keycodes using the USB GPIO channel 1
				printHex (kbdbuf.keycode[0] + (kbdbuf.keycode[1]<<8) + (kbdbuf.keycode[2]<<16) + + (kbdbuf.keycode[3]<<24), 1);
				//Modify to output the last 2 keycodes on channel 2.
				xil_printf("\n");
			}
			else if (device == 2) {
				rcode = mousePoll(&buf);
				if (rcode == hrNAK) {
					//NAK means no new data
					return;
				} else if (rcode) {
					xil_printf("Rcode: ");
					xil_printf("%x \n", rcode);
					return;
				}
				xil_printf("X displacement: ");
				xil_printf("%d ", (signed char) buf.Xdispl);
				xil_printf("Y displacement: ");
				xil_printf("%d ", (signed char) buf.Ydispl);
				xil_printf("Buttons: ");
				xil_printf("%x\n", buf.button);
			}
		} else if (GetUsbTaskState() == USB_STATE_ERROR) {
			if (!errorflag) {
				errorflag = 1;
				xil_printf("USB Error State\n");
				//print out string descriptor here
			}
		} else //not in USB running state
		{
			xil_printf("USB task state: ");
			xil_printf("%x\n", GetUsbTaskState());
			if (runningdebugflag) {	//previously running, reset USB hardware just to clear out any funky state, HS/FS etc
				runningdebugflag = 0;
				MAX3421E_init();
				USB_init();
			}
			errorflag = 0;
		}
}

void getSold(int index){
	int starting = 8*index;
	uint8_t bytes[8];
	for(int x = 0; x<8; x++){
		bytes[x] = 	hdmi_ctrl->SELL[starting+x];
		hdmi_ctrl->SELL[starting+x] = 0;
	}
	for(int x = 0; x<8; x++){
		printf("%d ",bytes[7-x]);
	}

}
int main() {
    init_platform();
    XGpio_Initialize(&Gpio_hex, XPAR_GPIO_USB_KEYCODE_DEVICE_ID);
   	XGpio_SetDataDirection(&Gpio_hex, 1, 0x00000000); //configure hex display GPIO
   	XGpio_SetDataDirection(&Gpio_hex, 2, 0x00000000); //configure hex display GPIO
	xil_printf("initializing MAX3421E...\n");
	MAX3421E_init();
	xil_printf("initializing USB...\n");
	USB_init();

	setup_game();
   	// int count = 0;
	// int count2 = 0;
	uint8_t keys [4];
	
	while (1) {
		get_input();
		for(int i = 0; i<4; i++){
			keys[i] = kbdbuf.keycode[i];
		}
		handle_input(keys);


		/*
		count++;
		uint8_t i [8];
		if(count == 10){
			count = 0;
			count2++;
			int y = ((hdmi_ctrl->SPAWNERS[1]&0xF)<<2)|((hdmi_ctrl->SPAWNERS[0]>>6) & 0x3);
			y++;
			y = y%50;
			hdmi_ctrl->SPAWNERS[0] = ((y&0x3)<<6)| (hdmi_ctrl->SPAWNERS[0] & 0x3F);
			hdmi_ctrl->SPAWNERS[1] =  (hdmi_ctrl->SPAWNERS[1] & 0xF0) | ((y&0xFC)>>2);
			if(count2 == 5){
				count2 = 0;
				for(int i = 0; i<50; i++){
					getSold(i);
					printf("\n");
				}
			}

		}
		*/


	}
    cleanup_platform();
	return 0;
}
