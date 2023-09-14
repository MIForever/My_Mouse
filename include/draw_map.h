#ifndef DRAW_MAP
#define DRAW_MAP

#include "map_process.h"

void draw_roads(proceed_map* pmap, int* errored);

void select_map(proceed_map* pmap);

final_map* format_map(proceed_map* pmap);

void print_map(final_map* fmap);

#endif