#include "../include/my_string.h"
#include "stdlib.h"
#include <unistd.h>
#include <stdio.h>

int my_strlen(char* string){
    int len=0;
    while(string[len]) len++;
    return len;
}

int string_to_int(char* string){
    int result=string[0]-'0';
    for(int i=1; i<my_strlen(string); i++){
        result = result*10+(string[i]-'0');
    }
    return result;
}

void skip_the_first_line(int fd, int* errored){
    char c;
    int readed;
    while((readed = read(fd,&c,1))){
        if(c=='\n'){
            return;
        }
    }
    *errored = 1;
}

int is_num(char* string){
    for(int i=0; i<my_strlen(string); i++){
        if(string[i]<'0' || string[i]>'9'){
            return 0;
        }
    }
    return 1;
}

void print_Error(){
    char error[] = "MAP ERROR";
    write(2,&error,my_strlen(error));
}

void proceed_size_map(char* map__size, char* size_x, char* size_y, int* errored){
    int x_found=0;
    for(int i=0; i<my_strlen(map__size) ; i++){
        if(map__size[i]=='x'){
            x_found=1;
            break;
        }
        size_y[i]=map__size[i];
    }
    if(!x_found){
        *errored=1;
        return;
    }

    int index=0;
    for(int i=my_strlen(size_y)+1; map__size[i]; i++){
        size_x[index]=map__size[i];
        index++;
    }
    if(!is_num(size_x) || !is_num(size_y)){
        *errored=1;
        return;
    }
}