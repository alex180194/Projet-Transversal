#ifndef UART0_H
#define UART0_H

void UART0_clock_init(void);
void UART0_registers_init(void);
void UART0_init(void);
char UART0_putchar (char c,char csg_tempo);
char UART0_getchar (void);

#endif