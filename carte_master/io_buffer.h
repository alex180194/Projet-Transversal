#ifndef IO_BUFFER_H
#define IO_BUFFER_H

#define BUFFER_SIZE 20

typedef struct io_buffer {
	char buffer[20];
	char indice;
}IO_buffer;

#endif