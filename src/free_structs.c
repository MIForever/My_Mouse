#include "../include/free_structs.h"

void free_row_map(row_map* rmap){
    for(int i=0; i<rmap->size_y; i++){
        free(rmap->map[i]);
    }
    free(rmap->map);
}

void free_proceed_map(proceed_map* pmap){
    for(int i=0; i<pmap->size_y; i++){
        free(pmap->map[i]);
    }
    free(pmap->map);
}

void free_final_map(final_map* fmap){
    for(int i=0; i<fmap->size_y; i++){
        free(fmap->map[i]);
    }
    free(fmap->map);
}