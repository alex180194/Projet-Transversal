#include "io_buffer.h"

void iobc_mempool_init(void){
	unsigned char xdata malloc_mempool [0x1000];
	init_mempool (&malloc_mempool, sizeof(malloc_mempool));
}

void iobc_init(IO_buffer_circulaire* iobc,char b_size)
{
	iobc->bottom=malloc(b_size);
	iobc->debut=iobc->bottom;
	iobc->fin=iobc->bottom;
	iobc->top=iobc->bottom+b_size;
}

char* iobc_increase_ptr(IO_buffer_circulaire iobc,char* ptr){
	char* new_ptr=ptr;
	new_ptr++;
	if(new_ptr==iobc.top)
		new_ptr=iobc.bottom;
	return new_ptr;
}

char iobc_is_empty(IO_buffer_circulaire iobc){
	if(iobc.debut==iobc.fin)
		return 1;
	return 0;
}

char iobc_get_char(IO_buffer_circulaire* iobc){
	char c;
	if(iobc_is_empty(*iobc))
		return 0;
	c=*iobc->debut;
	iobc->debut=iobc_increase_ptr(*iobc,iobc->debut);
	return c;
}

char iobc_is_full(IO_buffer_circulaire iobc){
	if(iobc_increase_ptr(iobc,iobc.debut)==iobc.fin)
		return 1;
	return 0;
}

char iobc_put_char(IO_buffer_circulaire* iobc,char c){
//	if(iobc_is_full(*iobc))
//		return 0;
	*iobc->fin=c;
	iobc->fin=iobc_increase_ptr(*iobc,iobc->fin);
	return 1;
}

char iobc_espace_libre(IO_buffer_circulaire iobc){
	char i=0;
	while(!iobc_is_full(iobc)&&i<(iobc.top-iobc.bottom)){
		iobc_increase_ptr(iobc,iobc.fin);
		i++;
	}
	return i;
}

char iobc_print(IO_buffer_circulaire *iobc,char* str){
	char i=0;
	while(str[i]!=0&&i<(iobc->top-iobc->bottom))
		i++;
	i++;
	if(i>iobc_espace_libre(*iobc))
		return 0;
	i=0;
	while(str[i]!=0){
		iobc_put_char(iobc,str[i]);
//		*iobc->fin=str[i];
//		iobc->fin=iobc_increase_ptr(*iobc,iobc->fin);
		i++;
	}
	iobc_put_char(iobc,0);
	return 1;
}