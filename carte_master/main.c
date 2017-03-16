#include "global_configuration.h"
#include "UART0.h"

int main(){
	char c;
	device_init();
	while(1){
		c=UART0_getchar();
		if(c!=0)
			UART0_putchar (c,2);
	}
	return 0;
}
