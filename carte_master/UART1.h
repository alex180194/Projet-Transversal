#ifndef UART1_H
#define UART1_H
//void UART1_clock_init(void);
// initialise l'uart 1 en mode 8 bit et qui utilise le timer 1
void UART1_registers_init(void);
void UART1_init(void);
char UART1_Putchar (char c,char csg_tempo);
char UART1_Getchar (void);
#endif