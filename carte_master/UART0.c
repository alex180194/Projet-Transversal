#include <c8051f020.h>    // SFR declarations
#include <stdio.h>
#include <intrins.h>
#include "UART0.h"


#ifndef SYSCLK
#define SYSCLK 22118400 
#endif
#define UART0_BAUDRATE 19200

#include "io_buffer.h"

IO_buffer xdata out_buf,in_buf;
char c=0;

void UART0_clock_init(void){
    CKCON |= 0x10; // Timer1 uses SYSCLK as time base
    TMOD = 0x20; // TMOD: timer 1, mode 2, 8-bit reload
    TMOD &= 0x2F;  // Met tous les autres bits à '0'
    TF1 =0; //flag désactivé
    TH1 = -(SYSCLK/UART0_BAUDRATE/16); // set Timer1 reload value for baudrate
    TL1 = TH1; // set Timer1 initial value
    TR1 = 1; // start Timer1
}

void UART0_registers_init(void){
		ES0=1;//enable uart0 interrupt
    RCLK0 = 0; //T2CON source CLK timer1
    TCLK0 = 0; //T2CON
    PCON |= 0x80; //SMOD0
    PCON &= 0xBF; //SSTAT0=0
    SCON0 = 0x72; //mode 1 : check stop bit - reception validée
}


void ISR_UART0(void) interrupt 4{
	char c=0;
	if(TI0){
		c=io_buffer_pop_front_ISR0(&out_buf);
		SBUF0=c;
		TI0=0;
	}
	else{
		if(RI0){
			c=SBUF0;
			if(c=='\r'||c=='\n')
				c=0;
      io_buffer_push_back_ISR0(&in_buf,c);
			RI0=0;
		}
	}
}

void UART0_init(void){
	UART0_clock_init();
	UART0_registers_init();
	io_buffer_init(&out_buf);
	io_buffer_init(&in_buf);
}

char UART0_print(char* str){
	return io_buffer_print(&out_buf,str);
}

char UART0_scan(char* str){
	return io_buffer_scan(&in_buf,str);
}