#include "./include/draw_map.h"
#include "./include/free_structs.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char** argv){
    if(argc==2){
        int map_size_x;
        int map_size_y;
        int errored = 0;
        int fd = open(argv[1],O_RDONLY);
        get_map_size(fd, &map_size_x, &map_size_y, &errored);
        if(errored){
            print_Error();
            return 1;
        }
        skip_the_first_line(fd,&errored);
        if(errored){
            print_Error();
            return 1;
        }
        row_map* map = to_row_map(fd, map_size_x, map_size_y, &errored);
        if(errored){
            print_Error();
            return 1;
        }
        proceed_map* int_map = row_to_int_map(map,&errored);
        free_row_map(map);
        free(map);
        if(errored){
            print_Error();
            return 1;
        }
        draw_roads(int_map, &errored);
        if(errored){
            print_Error();
            return 1;
        }
        select_map(int_map);
        final_map* fin_map = format_map(int_map);
        free_proceed_map(int_map);
        free(int_map);
        print_map(fin_map);
        free_final_map(fin_map);
        free(fin_map);
    }
    return 0;
}