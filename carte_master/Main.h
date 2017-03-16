 /*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: TP_8051_Lib.H
; 	TARGET MCUs	: C8051F020, 
; 	DESCRIPTION	: Configuration pour le TP EMBARQUE
;
; 	REVISION 1.0
;
;---------------------------------------------------------------------------*/
#ifndef __Main__
#define __Main__

#define SYSCLK 22118400 //approximate SYSCLK frequency in Hz
#define BAUDRATE  115200           // Baud rate of UART in bps
#define TICK_CLK  200  // (en hertz)


// Typedefs (see Chap 5)  
typedef unsigned char tByte;
typedef unsigned int  tWord;
typedef unsigned long tLong;

// Interrupts (see Chap 7)  
#define INTERRUPT_External_Interrupt_INT0 0
#define INTERRUPT_Timer_0_Overflow 1
#define INTERRUPT_External_Interrupt_INT1 2
#define INTERRUPT_Timer_1_Overflow 3
#define INTERRUPT_Timer_2_Overflow 5


#endif


