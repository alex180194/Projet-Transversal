#ifndef IO_BUFFER_H
#define	IO_BUFFER_H

#define BUFFER_SIZE 20

typedef struct io_buffer{
    char buffer[BUFFER_SIZE];
    char* debut;
    char* fin;
    char nbr_car;
    char nbr_string;
}IO_buffer;

void io_buffer_init(IO_buffer* buf);
char io_buffer_push_back(IO_buffer* buf,char car);
char io_buffer_push_back_ISR0(IO_buffer* buf,char car);
char io_buffer_push_back_ISR1(IO_buffer* buf,char car);
char io_buffer_pop_front(IO_buffer* buf);
char io_buffer_pop_front_ISR0(IO_buffer* buf);
char io_buffer_pop_front_ISR1(IO_buffer* buf);
char io_buffer_print(IO_buffer* buf,char* str);
char io_buffer_scan(IO_buffer* buf,char* str);

#endif	/* IO_BUFFER_H */