#ifndef UART0_H
#define UART0_H

void ISR_UART0(void);

void UART0_clock_init(void);
void UART0_registers_init(void);
void UART0_init(void);
char UART0_putchar (char c,char csg_tempo);
char UART0_getchar (void);
char UART0_print(char* str );
char UART0_scan(char* str);
void itoa(int n, char *s);

#endif