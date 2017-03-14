#include "global_configuration.h"
#include "UART0.h"
#include <c8051f020.h> 

void oscillator_init(void)
{
    int i = 0;
    OSCXCN    = 0x65;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    OSCICN    = 0x0C;
}
  
void watchdog_init(void)
{
        // Init du watchdog
        WDTCN = 0xde;                //On desactive le Watchdog Timer   
        WDTCN = 0xad;                //En mettant WDTCN à 0xde puis 0xad (page 131) 
}

void interrupts_init(void)
{
    IE        = 0x82;
    EIE1      |= 0x08;
}

void GPIO_init()
{
    // P0.0  -  TX0 (UART0), Open-Drain, Digital
    // P0.1  -  RX0 (UART0), Open-Drain, Digital
    // P0.2  -  SCK  (SPI0), Open-Drain, Digital
    // P0.3  -  MISO (SPI0), Open-Drain, Digital
    // P0.4  -  MOSI (SPI0), Open-Drain, Digital
    // P0.5  -  NSS  (SPI0), Open-Drain, Digital
    // P0.6  -  CEX0 (PCA),  Open-Drain, Digital
    // P0.7  -  Unassigned,  Open-Drain, Digital
 
    // P1.0  -  Unassigned,  Open-Drain, Digital
    // P1.1  -  Unassigned,  Open-Drain, Digital
    // P1.2  -  Unassigned,  Open-Drain, Digital
    // P1.3  -  Unassigned,  Open-Drain, Digital
    // P1.4  -  Unassigned,  Open-Drain, Digital
    // P1.5  -  Unassigned,  Open-Drain, Digital
    // P1.6  -  Unassigned,  Open-Drain, Digital
    // P1.7  -  Unassigned,  Open-Drain, Digital
 
    // P2.0  -  Unassigned,  Open-Drain, Digital
    // P2.1  -  Unassigned,  Open-Drain, Digital
    // P2.2  -  Unassigned,  Open-Drain, Digital
    // P2.3  -  Unassigned,  Open-Drain, Digital
    // P2.4  -  Unassigned,  Open-Drain, Digital
    // P2.5  -  Unassigned,  Open-Drain, Digital
    // P2.6  -  Unassigned,  Open-Drain, Digital
    // P2.7  -  Unassigned,  Open-Drain, Digital
 
    // P3.0  -  Unassigned,  Open-Drain, Digital
    // P3.1  -  Unassigned,  Open-Drain, Digital
    // P3.2  -  Unassigned,  Open-Drain, Digital
    // P3.3  -  Unassigned,  Open-Drain, Digital
    // P3.4  -  Unassigned,  Open-Drain, Digital
    // P3.5  -  Unassigned,  Open-Drain, Digital
    // P3.6  -  Unassigned,  Open-Drain, Digital
    // P3.7  -  Unassigned,  Open-Drain, Digital
         
    P1MDOUT   = 0x40; //LED
 
    XBR0      = 0x0E;
    XBR2      = 0x40;
		//XBR2			!= 0x
}

void device_init(void){
	oscillator_init();
	watchdog_init();
	GPIO_init();
	interrupts_init();
	
	UART0_init();
}
