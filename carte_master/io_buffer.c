#include "io_buffer.h"

void io_buffer_init(IO_buffer* buf){
    buf->debut=buf->buffer;
    buf->fin=buf->buffer;
    buf->nbr_car=0;
    buf->nbr_string=0;
}

char io_buffer_push_back(IO_buffer* buf,char car){
    if(buf->nbr_car>=BUFFER_SIZE)
        return 0;
    *buf->fin=car;
    buf->fin++;
    if(buf->fin>=buf->buffer+BUFFER_SIZE)
        buf->fin=buf->buffer;
    buf->nbr_car++;
    if(car==0)
        buf->nbr_string++;
    return 1;
}

char io_buffer_pop_front(IO_buffer* buf){
    char car;
    if(buf->nbr_car==0)
        return 0;
    car=*buf->debut;
    buf->debut++;
    if(buf->debut>=buf->buffer+BUFFER_SIZE)
        buf->debut=buf->buffer;
    buf->nbr_car--;
    if(car==0)
        buf->nbr_string--;
    return car;
}

char io_buffer_print(IO_buffer* buf ,char* str){
    char i=0;
    while(str[i]!=0&&i<BUFFER_SIZE)
        i++;
    if(i>=(BUFFER_SIZE-buf->nbr_car))
        return 0;
    i=0;
    while(str[i]!=0){
        io_buffer_push_back(buf,str[i]);
        i++;
    }
    io_buffer_push_back(buf,str[i]);
    return 1;
}

char io_buffer_scan(IO_buffer* buf,char* str){
    char c=5,i=0;
    if(buf->nbr_string==0)
        return 0;
    while(c!=0){
        c=io_buffer_pop_front(buf);
        str[i]=c;
        i++;
    }
    str[i]=0;
    return 1;
}