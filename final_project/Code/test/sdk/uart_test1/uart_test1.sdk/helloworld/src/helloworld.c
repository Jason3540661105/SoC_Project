/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */
//initial head file
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

//additional head file
#include "xparameters.h"
#include "xscugic.h"		//�]�t���_�޲z�M�B�z���������
#include "xil_exception.h"	//���`�B�z�M���_�B�̪���ƻP�w�q
#include "xgpio.h"			//
#include "xuartps.h"		//�]�tUART�����o���
#include "sleep.h"			//����ɶ����

// Parameter definitions
#define INTC_DEVICE_ID 			XPAR_PS7_SCUGIC_0_DEVICE_ID
#define LEDS_DEVICE_ID			XPAR_AXI_GPIO_0_DEVICE_ID					//led8bits
#define BTNS_DEVICE_ID			XPAR_AXI_GPIO_1_DEVICE_ID					//btn5bits

#define INTC_GPIO_INTERRUPT_ID 	XPAR_FABRIC_AXI_GPIO_1_IP2INTC_IRPT_INTR	//
#define BTN_INT 				XGPIO_IR_CH1_MASK


XUartPs_Config *Config_1;	//�ŧi�@��"Config_1"�������ܼơA�èϥΡuXUartPs_Config�v�����c
XUartPs Uart_PS_1;			//Declare The instance of the UART Driver

XGpio LEDInst, BTNInst;
XScuGic INTCInst;


static int led_data;
static int btn_value;

//----------------------------------------------------
// PROTOTYPE FUNCTIONS (�ۤv�g�����)
//----------------------------------------------------

/*static : ���w��ܥu��b�Ӥ��ϥΡA����Q��L�{���ե�*/

//1. UART-Send Data-Partial
static int Uart_Init(void);


//2. Button-interrupt-partial
static int 	InterruptSystemSetup(XScuGic *XScuGicInstancePtr);
static int 	IntcInitFunction_BTN(u16 DeviceId, XGpio *GpioInstancePtr);
static void	BTN_Intr_Handler(void *baseaddr_p);
static int	Uart_HelloWorld(void *InstancePtr);

int main()
{
    init_platform();
    int status;

    	// Initialise LEDs
    	status = XGpio_Initialize(&LEDInst, LEDS_DEVICE_ID);
    	if (status != XST_SUCCESS)
    		return XST_FAILURE;

    	// Initialise Push Buttons
    	status = XGpio_Initialize(&BTNInst, BTNS_DEVICE_ID);
    	if (status != XST_SUCCESS)
    		return XST_FAILURE;

    	// Initialise UART Setup
    	if(Uart_Init() == XST_FAILURE){
    		return XST_FAILURE;
    	}
    	else{
    		Uart_HelloWorld(&Uart_PS_1);
    	}

    	// Set LEDs direction to outputs
    	XGpio_SetDataDirection(&LEDInst, 1, 0x00);

    	// Set all buttons direction to inputs
    	XGpio_SetDataDirection(&BTNInst, 1, 0xFF);

    	// Initialize interrupt controller
    	status = IntcInitFunction_BTN(INTC_DEVICE_ID, &BTNInst);
    	if (status != XST_SUCCESS)
    		return XST_FAILURE;

    	XGpio LED_XGpio;			// �ŧi�@��GPIO�Ϊ����c.
    	int LED_num = 0b00000000;	// �ŧi�@���ܼ�,���B��μȦs��.

    	XGpio_Initialize(&LED_XGpio, XPAR_AXI_GPIO_0_DEVICE_ID);	// ��l��LED_XGpio.�ós����AXI_GPIO_0���]��
    	XGpio_SetDataDirection(&LED_XGpio, 1, 0x00);				// �]�m�q�D.(&LED_XGpio, 1, 0) 0��0x00�N����ƿ�X

    	printf("\nStart!!!\n");

    	while(1) {
    			LED_num = LED_num + 1;
    	    	//printf("Main Count_LED_num = 0x%d\n", LED_num);
    	    	//XGpio_DiscreteWrite(&LED_XGpio, 1, LED_num);		// LED_XGpio�q�D,�eLED_num�ȶi�h.
    	    	usleep(500000);
    	    }
    	return 0;
    cleanup_platform();
    return 0;
}


//----------------------------------------------------
// 1. UART-Send Data-Partial
//----------------------------------------------------

//1.1 UART-Setup-initialization
int Uart_Init(void){
	int status = 0;

	/*1.�b�uxparameters.h�v���M��u�O�_���ŦX�v���]��ID*/
	Config_1 = XUartPs_LookupConfig(XPAR_XUARTPS_0_DEVICE_ID);
	if (NULL == Config_1) {
		return XST_FAILURE;
	}

	/*UART��l�ƽT�{�ˬd*/
	status = XUartPs_CfgInitialize(&Uart_PS_1, Config_1, Config_1->BaseAddress);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	/*�]�mUART��BaudRate*/
	status = XUartPs_SetBaudRate(&Uart_PS_1,115200);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	/*�]�mUART���ާ@�Ҧ�*/
	XUartPs_SetOperMode(&Uart_PS_1, XUARTPS_OPER_MODE_NORMAL);


	XUartPs_WriteReg(Uart_PS_1.Config.BaseAddress,XUARTPS_TXWM_OFFSET, 0x20U);
	//#define XUARTPS_TXWM_OFFSET		0x0044U  /**< TX FIFO Trigger Level [5:0] */

	return XST_SUCCESS;

}
//1.2 UART-Send-Data ?
int Uart_HelloWorld(void *InstancePtr){
	int SentCount = 0;

	//u8 HelloWorld[] = "Hello_World";
	/*
	while (SentCount < (sizeof(HelloWorld) - 1)) {
		SentCount += XUartPs_Send(&Uart_PS_1,&HelloWorld[SentCount], 1);
	}
	*/

	char init_map[16] = "1,2,3,4,5,6,7,8";
	while (SentCount < (sizeof(init_map)-1)) {
		SentCount += XUartPs_Send(&Uart_PS_1,(u8*)&init_map[SentCount], 1);
	}
	return SentCount;
}


//----------------------------------------------------
// 2. Button-interrupt-partial
//----------------------------------------------------

//2.1 ����button interrupt����l�Ƴ]�w
int InterruptSystemSetup(XScuGic *XScuGicInstancePtr) {
	// Enable interrupt
	XGpio_InterruptEnable(&BTNInst, BTN_INT);
	XGpio_InterruptGlobalEnable(&BTNInst);

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler) XScuGic_InterruptHandler,
			XScuGicInstancePtr);
	Xil_ExceptionEnable();

	return XST_SUCCESS;

}

int IntcInitFunction_BTN(u16 DeviceId, XGpio *GpioInstancePtr) {
	XScuGic_Config *IntcConfig;
	int status;

	// Interrupt controller initialisation
	IntcConfig = XScuGic_LookupConfig(DeviceId);
	status = XScuGic_CfgInitialize(&INTCInst, IntcConfig,
			IntcConfig->CpuBaseAddress);
	if (status != XST_SUCCESS)
		return XST_FAILURE;

	// Call to interrupt setup
	status = InterruptSystemSetup(&INTCInst);
	if (status != XST_SUCCESS)
		return XST_FAILURE;

	// Connect GPIO interrupt to handler
	status = XScuGic_Connect(&INTCInst, INTC_GPIO_INTERRUPT_ID,
			(Xil_ExceptionHandler) BTN_Intr_Handler, (void *) GpioInstancePtr);
	if (status != XST_SUCCESS)
		return XST_FAILURE;

	// Enable GPIO interrupts interrupt
	XGpio_InterruptEnable(GpioInstancePtr, 1);
	XGpio_InterruptGlobalEnable(GpioInstancePtr);

	// Enable GPIO and timer interrupts in the controller
	XScuGic_Enable(&INTCInst, INTC_GPIO_INTERRUPT_ID);

	return XST_SUCCESS;
}

//2.2 Button interrupt�ɷ|�@�����e
void BTN_Intr_Handler(void *InstancePtr) {

	// Disable GPIO interrupts
	XGpio_InterruptDisable(&BTNInst, BTN_INT);
	// Ignore additional button presses
	if ((XGpio_InterruptGetStatus(&BTNInst) & BTN_INT) != BTN_INT) {
		return;
	}
	btn_value = XGpio_DiscreteRead(&BTNInst, 1);
	// Increment counter based on button value
	// Reset if centre button pressed
	if (btn_value != 1)
	{
		printf("Interrupt\n");
		led_data = led_data + btn_value;
		printf("Button Value is : %d\n",btn_value);
		printf("intterupt_led_data = 0x%d\n", led_data);
		usleep(20000); //sleep ���T�w
	}
	else
	{
		led_data = 0;
	}

	XGpio_DiscreteWrite(&LEDInst, 1, led_data);
	(void) XGpio_InterruptClear(&BTNInst, BTN_INT);
	// Enable GPIO interrupts
	XGpio_InterruptEnable(&BTNInst, BTN_INT);
}