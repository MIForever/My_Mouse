#ifndef MY_STRING_H
#define MY_STRING_H

#include "stdlib.h"
#include <unistd.h>
#include <stdio.h>

int my_strlen(char* string);

int string_to_int(char* string);

void skip_the_first_line(int fd, int* errored);

int is_num(char* string);

void print_Error();

void proceed_size_map(char* map__size, char* size_x, char* size_y, int* errored);

#endif