#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct row_map{
    char** map;
    unsigned short size_x;
    unsigned short size_y;
} row_map;

typedef struct proceed_map{
    int** map;
    int entrance_x_y[3];
    int exit_x_y[3];
    unsigned short size_x;
    unsigned short size_y;
} proceed_map;

typedef struct final_map{
    char** map;
    unsigned short size_x;
    unsigned short size_y;
    int steps;
} final_map;

#endif