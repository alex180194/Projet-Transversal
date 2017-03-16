#include <c8051f020.h>    // SFR declarations
#include <stdio.h>
#include <intrins.h>

#include "UART1.h"
#ifndef SYSCLK
#define SYSCLK 22118400 
#endif
#define UART1_BAUDRATE 11500


/*void UART1_clock_init(){
	
}*/
void UART1_init(void){
	//SCON1: UART1 Control Register
	T4CON&=~0x30;
	PCON |= 0x10;
	PCON&=~0x08;
	SCON1=0x72;
}

char UART1_putchar (char c,char csg_tempo){
	int i=0;
	while((SCON1&0x02)==0)
	{
		for(i=0;i<1000;i++)
		{
			_nop_ ();
		}
		
		csg_tempo--;
		if(csg_tempo==0)
		{
			return 0;
		}
	}
	SBUF1=c;
	SCON1&=~0x02;
	return c;
}

char UART1_getchar (void){
    char c;
    if ((SCON1&0x01)==0)
        return 0;
       
    c=SBUF1;
    SCON1&=~0x01;
    return c;
}