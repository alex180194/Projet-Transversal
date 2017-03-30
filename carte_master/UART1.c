#include <c8051f020.h>    // SFR declarations
#include <stdio.h>
#include <intrins.h>

#include "UART1.h"
#ifndef SYSCLK
#define SYSCLK 22118400 
#endif
#define UART1_BAUDRATE 11500

#include "io_buffer.h"

IO_buffer xdata inb_UART1={"",0},outb_UART1={"",0};

/*void UART1_clock_init(){
	
}*/
void UART1_init(void){
	//SCON1: UART1 Control Register
	T4CON&=~0x30;
	PCON |= 0x10;
	PCON&=~0x08;
	SCON1=0x73;
	EIE2|=0x40;//enable uart1 interrupt
}

void ISR_UART1(void) interrupt 20{
	char c=0;
	if(SCON1&0x02){
		if(outb_UART1.indice!=BUFFER_SIZE+1){
			UART1_putchar(outb_UART1.buffer[outb_UART1.indice],2);
			if(outb_UART1.buffer[outb_UART1.indice]==0||outb_UART1.indice==(BUFFER_SIZE-1)){
				outb_UART1.indice=BUFFER_SIZE+1;
			}
			else{
				++outb_UART1.indice;
			}
		}
		SCON1&=~0x02;
	}
	else{
		if(SCON1&0x01){
			c=UART1_getchar();
			if(c!=0){
				if(c==13||c==10)
					c=0;
				if(inb_UART1.indice<BUFFER_SIZE){
					inb_UART1.buffer[inb_UART1.indice]=c;
					inb_UART1.indice++;
				}
				if(c==0||inb_UART1.indice==BUFFER_SIZE)
					inb_UART1.indice=BUFFER_SIZE+1;
			}
	    SCON1&=~0x01;
		}
	}
}

char UART1_print(char* str){
	char i=0;
	char c=5;
	if(outb_UART1.indice!=BUFFER_SIZE+1)
		return 0;
	while(str[i]!=0)
		i++;
	if(i>=BUFFER_SIZE)
		return 0;
	i=0;
	outb_UART1.indice=0;
	while(c!=0){
		c=str[i];
		outb_UART1.buffer[i]=c;
		i++;
	}
	return 1;
}

char UART1_scan(char* str){
	char c=5;
	char i=0;
	if(inb_UART1.indice!=BUFFER_SIZE+1){
		str[0]=0;
		return 0;
	}
	while(c!=0&&i<BUFFER_SIZE){
		c=inb_UART1.buffer[i];
		str[i]=c;
		inb_UART1.buffer[i]=5;
		i++;
	}
	if(c!=0){
		str[0]=0;
		inb_UART1.indice=0;
		return 0;
	}
	inb_UART1.indice=0;
	return 1;
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