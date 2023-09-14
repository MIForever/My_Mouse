#ifndef FREE_STRUCTS_H
#define FREE_STRUCTS_H

#include "structs.h"
#include <stdlib.h>

void free_row_map(row_map* rmap);

void free_proceed_map(proceed_map* pmap);

void free_final_map(final_map* fmap);

#endif