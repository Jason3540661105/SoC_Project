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


#include "Sokoban.h"		//���c�l�C������ܮw


// Parameter definitions
#define INTC_DEVICE_ID 			XPAR_PS7_SCUGIC_0_DEVICE_ID
#define LEDS_DEVICE_ID			XPAR_AXI_GPIO_0_DEVICE_ID					//led8bits
#define BTNS_DEVICE_ID			XPAR_AXI_GPIO_1_DEVICE_ID					//btn5bits

#define INTC_GPIO_INTERRUPT_ID 	XPAR_FABRIC_AXI_GPIO_1_IP2INTC_IRPT_INTR	//�ڲq�O[PS]�]�w�����_���f
#define BTN_INT 				XGPIO_IR_CH1_MASK



//volatile�w�q : �C���X�ݮɱq�O���餤���sŪ�����
volatile static u32 ByteSend = 0 , TotalByteSend = 0;
//volatile static int map[Map1_HEIGHT][Map1_WIDTH]= {0};						//�s��a�ϰ}�C��ƪ����
//volatile static int map_test[Map1_HEIGHT][Map1_WIDTH]= {0};				//�s��a�ϰ}�C��ƪ����-test

static int Sokoban_Game_State = 0;											//������:0   ����:1
static int map[Map1_HEIGHT][Map1_WIDTH]= {0};								//�s��a�ϰ}�C��ƪ����
static int Remaining_Destinations_led;										//��ܳѾl�ت��a�ƶq��led
static int led_data;														//��ܳѾl�ت��a�ƶq��led
static int btn_value;
static u8 TransmitBuffer[Map1_HEIGHT * Map1_WIDTH + 1] = {0};				//�x�s�ഫ��[map���@���}�C]+[�P�_�C���O�_����]�A�@��:73bits

static int Person_X;														//X�b���H���y��
static int Person_Y;														//Y�b�H���y��


XUartPs_Config *Config_1;													//�ŧi"Config_1"�������ܼơA�èϥΡuXUartPs_Config�v�����c (UART�]�ƪ��]�w)
XUartPs Uart_PS_1;															//�ŧiUart_PS_1��XUartPs�����c (XUartPs�X�ʵ{����Ҹ�Ƶ��c)

XGpio LEDInst, BTNInst;														//�ŧiLEDInst,BTNInst��XGpio�����c
XScuGic INTCInst;															//�ŧiINTCInst��XScuGic�����c

//----------------------------------------------------
// PROTOTYPE FUNCTIONS (�ۤv�g�����)
//----------------------------------------------------

/*static : ���w��ܥu��b�Ӥ��ϥΡA����Q��L�{���ե�*/
//1. UART-Send Data-Partial
static int	Uart_Init(void);
static int	Uart_SendData_test(void *InstancePtr);

//2. Button-interrupt-partial
static int 	InterruptSystemSetup(XScuGic *XScuGicInstancePtr);
static int 	IntcInitFunction_BTN(u16 DeviceId, XGpio *GpioInstancePtr);
static void	BTN_Intr_Handler(void *baseaddr_p);

//----------------------------------------------------
// 0. Main Function
//----------------------------------------------------
int main()
{
	init_platform();														//��l��UART�B�P��֨�
	int status;																//�]�Ƴ]�ƪ�l�ƬO�_���\���ܼ�

	//��l�Ʀa��
	Initial_Map(map, init_map);												//�ۭq�禡(���e�a��, ��l�a��)

    // ��l��LED
    status = XGpio_Initialize(&LEDInst, LEDS_DEVICE_ID);					//��l��XGpio (���V GPIO ���, �]��ID�W��)
    if (status != XST_SUCCESS)												//�P�_ GPIO ��l��
    	return XST_FAILURE;													//���ѴN�����{��

    // ��l��BTN
    status = XGpio_Initialize(&BTNInst, BTNS_DEVICE_ID);					//��l��XGpio (���V GPIO ���, �]��ID�W��)
    if (status != XST_SUCCESS)												//�P�_ GPIO ��l��
    	return XST_FAILURE;													//���ѴN�����{��

    //�]�w GPIO ��J/��X
    XGpio_SetDataDirection(&LEDInst, 1, 0x00);								//�]�w GPIO ��J/��X (���V GPIO ���, GPIO���q�D , ��V�]�w 0:output 1:input)
    XGpio_SetDataDirection(&BTNInst, 1, 0xFF);								//�]�w GPIO ��J/��X (���V GPIO ���, GPIO���q�D , ��V�]�w 0:output 1:input)

    //��l��UART
    if(Uart_Init() == XST_FAILURE){											//�P�_ UART ��l��
    	return XST_FAILURE;													//���ѴN�����{��
	}
    else{
    	printf("Uart Initialization Successful!\n");
    	Uart_SendData_test(&Uart_PS_1);										//UART ��l�Ʀ��\��۰ʶǿ�@�� UART ���
	}

    //��l�Ƥ��_���
    status = IntcInitFunction_BTN(INTC_DEVICE_ID, &BTNInst);				//�ۭq�禡 (�]��ID ,GPIO ���)
    if (status != XST_SUCCESS)												//�P�_���_�����l��
    	return XST_FAILURE;													//���ѴN�����{��

    XGpio LED_XGpio;														//�ŧi LED_XGpio �� XGpio �����c
    XGpio_Initialize(&LED_XGpio, XPAR_AXI_GPIO_0_DEVICE_ID);				//��l�� LED_XGpio �ós���� AXI_GPIO_0 ���]��

    while(1){
    	if(isWinner(map)){													//�ۭq���L�禡�P�_�O�_�q�� (���e�a��)
    		printf("Winner!\n");
    		printf("Do you wnat to play again?\n");
    		if(btn_value == 0)
    		    break;
    	}
    	else{
    		//�P�_�C�����A
    		Judge_Game_State(&Sokoban_Game_State, map);								//�ۭq�禡(�C�����A, ���e�a��)
    		printf("Sokoban_Game_State is [%d]\n", Sokoban_Game_State);

    		//LED��ܳѾl�\��ت��a�ƶq
    		//Remaining_Destinations_led = Remaining_Destinations(map);				//�ϥΤG���a��
    		//Remaining_Destinations_led = Remaining_Destinations(TransmitBuffer);	//�ϥΤ@���a��

    		Remaining_Box(&Remaining_Destinations_led, map);				//�ۭq�禡(�Ѿl�ت��a�ƶq, ���e�a��)
    		XGpio_DiscreteWrite(&LED_XGpio, 1, Remaining_Destinations_led);			//�NLED����Ƽg�i���w��GPIO�q�D���Ȧs����	(XGpio�����, GPIO���q�D, �n�g�J�Ȧs�������)
    		printf("Remaining_Destinations_led = [%d]\n", Remaining_Destinations_led);

    		//�M��H���y��
    		Find_Person_Coordinates(&Person_X, &Person_Y, map);						//�ۭq�禡(X�b, Y�b)
    		printf("Person Coordinate is X[%d] Y[%d]\n", Person_X, Person_Y);
    		usleep(500000);
    	}
    }

    cleanup_platform();															//�����֨�
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

	/*(²��ӻ��N�OUART��FIFO�x�s��h��bits(�����q)�|Ĳ�o�ʧ@�A0x20U����Q�i�32
	 * �ҥHFIFO�x�s��32bits(8 Bytes)����Ʈɷ|Ĳ�o�ʧ@)
	*/
	XUartPs_WriteReg(Uart_PS_1.Config.BaseAddress,XUARTPS_TXWM_OFFSET, 0x20U);

	return XST_SUCCESS;

}

//1.2 UART-Send-Data
int Uart_SendData_test(void *InstancePtr){
	MapToArray_c(TransmitBuffer, map, Sokoban_Game_State);
	//MapToArray_c(TransmitBuffer, init_map, Sokoban_Game_State);
	//Print_Map_Data(TransmitBuffer);

	while (TotalByteSend < (sizeof(TransmitBuffer))) {
			ByteSend = XUartPs_Send(&Uart_PS_1,(u8*)&TransmitBuffer[TotalByteSend], 1);
			TotalByteSend += ByteSend;
	}
	TotalByteSend = 0;
	printf("\n");
	return TotalByteSend;
}

//----------------------------------------------------
// 2. Button-Interrupt-Partial
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

//2.2
int IntcInitFunction_BTN(u16 DeviceId, XGpio *GpioInstancePtr) {
	XScuGic_Config *IntcConfig;
	int status;

	// Interrupt controller initialisation
	IntcConfig = XScuGic_LookupConfig(DeviceId);
	status = XScuGic_CfgInitialize(&INTCInst, IntcConfig,IntcConfig->CpuBaseAddress);
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

//2.3 Button interrupt�ɷ|�@�����e
void BTN_Intr_Handler(void *InstancePtr){

	// Disable GPIO interrupts
	XGpio_InterruptDisable(&BTNInst, BTN_INT);

	// Ignore additional button presses
	if ((XGpio_InterruptGetStatus(&BTNInst) & BTN_INT) != BTN_INT) {
		return;
	}

	btn_value = XGpio_DiscreteRead(&BTNInst, 1);

	// Increment counter based on button value
	// Reset if centre button pressed
	if(btn_value != 1){
		switch(btn_value){

			case 16:{
				if(Sokoban_Game_State == 0){
					Move_Up(map, Person_X, Person_Y);
					Judge_Game_State(&Sokoban_Game_State, map);
					Uart_SendData_test(&Uart_PS_1);
					printf("\nMove UP : %d\n",btn_value);
					usleep(250000);
				}
				else
					Initial_Map(map, init_map);
			}break;

			case 2:{
				if(Sokoban_Game_State == 0){
					Move_Down(map, Person_X, Person_Y);
					Judge_Game_State(&Sokoban_Game_State, map);
					Uart_SendData_test(&Uart_PS_1);
					printf("\nMove Down : %d\n",btn_value);
					usleep(250000);
				}
				else
					Initial_Map(map, init_map);
			}break;

			case 4:{
				if(Sokoban_Game_State == 0){
					Move_Left(map, Person_X, Person_Y);
					Judge_Game_State(&Sokoban_Game_State, map);
					Uart_SendData_test(&Uart_PS_1);
					printf("\nMove Left : %d\n",btn_value);
					usleep(250000);
				}
				else
					Initial_Map(map, init_map);
			}break;

			case 8:{
				if(Sokoban_Game_State == 0){
					Move_Right(map, Person_X, Person_Y);
					Judge_Game_State(&Sokoban_Game_State, map);
					Uart_SendData_test(&Uart_PS_1);
					printf("\nMove Right : %d\n",btn_value);
					usleep(250000);
				}
				else
					Initial_Map(map, init_map);
			}break;

			case 0:{
				if(Sokoban_Game_State == 0){
					Game_Reset(map, init_map);
					Judge_Game_State(&Sokoban_Game_State, map);
					Uart_SendData_test(&Uart_PS_1);
					printf("\nReset Game : %d\n",btn_value);
					usleep(250000);
				}
				else{
				    printf("\ngame over\n");
					break;
				}
			}

			default:{
				printf("Error : Unknown btn_value\n");
			}break;
		}
	}
	else{
		led_data = 0;
	}
	XGpio_DiscreteWrite(&LEDInst, 1, led_data);
	(void) XGpio_InterruptClear(&BTNInst, BTN_INT);
	// Enable GPIO interrupts
	XGpio_InterruptEnable(&BTNInst, BTN_INT);
}

//----------------------------------------------------
// 3. Other Function Partial
//----------------------------------------------------
