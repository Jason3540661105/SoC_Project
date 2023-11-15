#include <stdio.h>
#include <stdlib.h>
#include "xparameters.h"	// �Ѽƶ�.
#include "xgpio.h"			// ²��PS��PL��GPIO�ާ@����Ʈw.

// �����.
void delay(int dly)
{
    int i, j;
    for (i = 0; i < dly; i++) {
    	for (j = 0; j < 0xffff; j++) {
    		;
        }
    }
}

// �D�{��.
int main()
{
    XGpio LED_XGpio;			// �ŧi�@��GPIO�Ϊ����c.
    XGpio SW_XGpio;				// �ŧi�@��GPIO�Ϊ����c.
    int LED_num = 0b00000000;	// �ŧi�@���ܼ�LED,���B��μȦs��.
    int SW_num 	= 0b00000000;	// �ŧi�@���ܼ�SW,���B��μȦs��.
    u32 dir;					// �ŧi�@��32�쪺�L�Ÿ���ƪ�dir.

    XGpio_Initialize(&LED_XGpio, XPAR_AXI_GPIO_0_DEVICE_ID);	// ��l��LED_XGpio.
    XGpio_SetDataDirection(&LED_XGpio, 1, 0);					// �]�m�q�D. 0 input
    dir = XGpio_GetDataDirection(&LED_XGpio, 1);
    printf("led1: %x\n",dir);

    XGpio_Initialize(&SW_XGpio, XPAR_AXI_GPIO_1_DEVICE_ID);		// ��l��LED_XGpio.
    XGpio_GetDataDirection(&SW_XGpio, 1);						// �]�m�q�D.    1 output
    dir = XGpio_GetDataDirection(&LED_XGpio, 1);
    printf("sw1: %x\n",dir);

    printf("Start!!!");

    while(1) {
    	SW_num	= XGpio_DiscreteRead(&SW_XGpio, 1);
    	LED_num = SW_num + 1;
    	XGpio_DiscreteWrite(&LED_XGpio, 1, LED_num);
    	delay(1000);
    }
    return 0;
}