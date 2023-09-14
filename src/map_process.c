#include "../include/map_process.h"

void get_map_size(int fd, int* x, int* y, int* errored){
    char c;
    char* size_of_the_map = calloc(18,sizeof(char));
    int readed = read(fd,&c,1);
    if(!readed){
            *errored=1;
            return;
        }
    for(int i=0; c!='*'; i++){
        size_of_the_map[i]=c;
        readed = read(fd,&c,1);
        if(!readed || c=='\n'){
            *errored=1;
            return;
        }
    }
    char* size_x = calloc(8,sizeof(char));
    char* size_y = calloc(8,sizeof(char));

    proceed_size_map(size_of_the_map, size_x, size_y, errored);
    if(*errored) return;

    *x=string_to_int(size_x);
    *y=string_to_int(size_y);

    free(size_of_the_map);
    free(size_x);
    free(size_y);
}


row_map* get_row_map(int size_x, int size_y){
    row_map* matrix_map = malloc(sizeof(row_map));
    matrix_map->map = calloc(size_y,sizeof(char*));
    for(int i=0; i<size_y; i++){
        matrix_map->map[i]=(char*)calloc(size_x+1,sizeof(char));
    }
    return matrix_map;
}


row_map* to_row_map(int fd, int size_x, int size_y, int* errored){
    row_map* matrix_map = get_row_map(size_x,size_y);

    char new_line;
    int readed;
    int readed_new_line;
    char curr;
    
    for(int i=0; i<size_y; i++){
        readed = read(fd,matrix_map->map[i],size_x);
        readed_new_line = read(fd, &new_line, 1);
        if(!readed_new_line || new_line!='\n' || readed!=size_x){
            *errored = 1;
            return matrix_map;
        }
        for(int j=0; j<readed; j++){
            curr=matrix_map->map[i][j];
            if (curr!='*' && curr!=' ' && curr!='1' && curr!='2'){
                *errored = 1;
                return matrix_map;
            }
        }
    }
    matrix_map->size_x = size_x;
    matrix_map->size_y = size_y;
    return matrix_map;
}

proceed_map* get_prcd_map(row_map* rmap){
    proceed_map* int_map = malloc(sizeof(proceed_map));
    int_map->size_x=rmap->size_x;
    int_map->size_y=rmap->size_y;
    int_map->map = calloc(rmap->size_y,sizeof(int*));
    for(int i=0; i<rmap->size_y; i++){
        int_map->map[i] = calloc(rmap->size_x+1,sizeof(int));
    }
    return int_map;
}

proceed_map* row_to_int_map(row_map* rmap, int* errored){
    proceed_map* int_map = get_prcd_map(rmap);

    int count1=0;
    int count2=0;

    for(int i=0; i<rmap->size_y; i++){
        for(int j=0; j<rmap->size_x; j++){
            if(rmap->map[i][j]=='*'){
                int_map->map[i][j]=1;
            }
            else if(rmap->map[i][j]==' '){
                int_map->map[i][j]=0;
            }

            else if(rmap->map[i][j]=='1'){
                int_map->map[i][j]=-1;
                int_map->entrance_x_y[0]=i;
                int_map->entrance_x_y[1]=j;
                if(count1){
                    *errored = 1;
                    return int_map;
                }
                count1++;
            }
            
            else if(rmap->map[i][j]=='2'){
                int_map->map[i][j]=-2;
                int_map->exit_x_y[0]=i;
                int_map->exit_x_y[1]=j;
                if(count2){
                    *errored = 1;
                    return int_map;
                }
                count2++;
            }
        }
    }
    *errored = (!count1 || !count2);
    return int_map;
}