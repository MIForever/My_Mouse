#ifndef MATRIX_FUNCTIONS
#define MATRIX_FUNCTIONS

#include "fcntl.h"
#include "my_string.h"
#include "structs.h"

void get_map_size(int fd, int* x, int* y, int* erroreds);

row_map* to_row_map(int fd, int size_x, int size_y, int* errored);

proceed_map* get_prcd_map(row_map* rmap);

proceed_map* row_to_int_map(row_map* map, int* errored);

#endif