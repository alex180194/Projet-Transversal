#include <c8051f020.h>    // SFR declarations
#include <stdio.h>
#include <intrins.h>

#include "UART1.h"
#ifndef SYSCLK
#define SYSCLK 22118400 
#endif
#define UART1_BAUDRATE 19200

#include "io_buffer.h"

IO_buffer xdata out_buf_UART1,in_buf_UART1;
char car=0;

/*void UART1_clock_init(){
	
}*/
void UART1_init(void){
	//SCON1: UART1 Control Register
	T4CON&=~0x30;
	PCON |= 0x10;
	PCON&=~0x08;
	SCON1=0x73;
	EIE2|=0x40;//enable uart1 interrupt
	
  io_buffer_init(&out_buf_UART1);
	io_buffer_init(&in_buf_UART1);
}

void ISR_UART1(void) interrupt 20{
	if(SCON1&0x02){
		if(out_buf_UART1.nbr_car>0){
			car=io_buffer_pop_front_ISR1(&out_buf_UART1);
			SBUF1=car;
		}
		SCON1&=~0x02;
	}
	else{
		if(SCON1&0x01){
			car=SBUF1;
			if(car=='\r'||car=='\n')
				car=0;
      io_buffer_push_back_ISR1(&in_buf_UART1,car);
	    SCON1&=~0x01;
		}
	}
}

char UART1_print(char* str){
	char cara=0,nb_cara=out_buf_UART1.nbr_car;
	cara= io_buffer_print(&out_buf_UART1,str);
	if(nb_cara==0)
		SCON1|=0x02;
	return cara;
}

char UART1_scan(char* str){
	return io_buffer_scan(&in_buf_UART1,str);
}