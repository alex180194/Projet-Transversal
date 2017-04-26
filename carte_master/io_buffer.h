#ifndef IO_BUFFER_H
#define IO_BUFFER_H

#define BUFFER_SIZE 20

#include <stdlib.h>

typedef struct io_buffer {
	char buffer[BUFFER_SIZE];
	char indice;
}IO_buffer;

typedef struct io_buffer_circulaire {
	char* bottom;
	char* debut;
	char* fin;
	char* top;
}IO_buffer_circulaire;

void iobc_mempool_init(void);
void iobc_init(IO_buffer_circulaire* iobc,char b_size);
char* iobc_increase_ptr(IO_buffer_circulaire iobc,char* ptr);
char iobc_is_empty(IO_buffer_circulaire iobc);
char iobc_get_char(IO_buffer_circulaire* iobc);
char iobc_is_full(IO_buffer_circulaire iobc);
char iobc_put_char(IO_buffer_circulaire* iobc,char c);
char iobc_espace_libre(IO_buffer_circulaire iobc);
char iobc_print(IO_buffer_circulaire *iobc,char* str);


#endif