#include <c8051f020.h>    // SFR declarations
#include <stdio.h>
#include <intrins.h>
#include "UART0.h"


#ifndef SYSCLK
#define SYSCLK 22118400 
#endif
#define UART0_BAUDRATE 11500

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
    RCLK0 = 0; //T2CON source CLK timer1
    TCLK0 = 0; //T2CON
    PCON |= 0x80; //SMOD0
    PCON &= 0xBF; //SSTAT0=0
    SCON0 = 0x72; //mode 1 : check stop bit - reception validée
}

void UART0_init(void){
	UART0_clock_init();
	UART0_registers_init();
}

char UART0_putchar (char c,char csg_tempo)
{
	int i=0;
	while(TI0==0)
	{
		for(i=0;i<1000;i++)
		{
			_nop_ ();
		}
		
		csg_tempo=csg_tempo-1;
		if(csg_tempo==0)
		{
			return 0;
		}
	}
	SBUF0=c;
	TI0=0;
	return c;
}

char UART0_getchar (void)
{
    char c;
    if (RI0==0)
        return 0;
       
    c=SBUF0;
    RI0=0;
    return c;
}

void UART0_print(char* str){
	int i=0;
	char c=0;
	while(str[i]!=0){
		c=0;
		while(c==0){
			c=UART0_putchar(str[i],2);
		}
		++i;
	}
}

void UART0_scan(char* str){
	int i=0;
	char c=5;
	//UART0_putchar('l',2);
	while(c!=0){
		c=0;
		while(c==0){
			c=UART0_getchar();
			//UART0_putchar('x',2);
		}
		//UART0_putchar('a',2);
		if(c==13||c==10){
			c=0;
		}
		str[i]=c;
		++i;
	}
}

void itoa(int n, char *s) { 
	char i;
	int n1;
	if (n<0) {
		n=-n;
		*s++='-';
		}
	do
	{
		n1=n;
		i=0;
	while (1) {
		if (n1<=9)   {
			*s++=n1+'0';
			break;
		}
		n1=n1/10;
		i++;
	}
	while (i) {
		i--;
		n1=n1*10;
	}
	n-=n1;
	}while (n);
	*s++=0;
}