#include "../include/draw_map.h"

void draw_roads(proceed_map* pmap, int* errored){
    int curr_road_num=2;
    int end_point_x;
    int end_point_y;
    if(pmap->exit_x_y[1]==pmap->size_x-1){
        end_point_x = pmap->exit_x_y[1]-1;
        end_point_y = pmap->exit_x_y[0];
    }
    else if(pmap->exit_x_y[0]==pmap->size_y-1){
        end_point_x = pmap->exit_x_y[1];
        end_point_y = pmap->exit_x_y[0]-1;
    }
    
    if(!pmap->entrance_x_y[1]) 
        pmap->map[pmap->entrance_x_y[0]][1]=curr_road_num;
    else if (!pmap->entrance_x_y[0]){
        pmap->map[1][pmap->entrance_x_y[1]]=curr_road_num;
    }

    int run=1;
    int run_2=1;
    int found;
    while(run){
        found=0;
        for (int i = 0; i < pmap->size_y && run_2; i++) {
            for (int j = 0; j < pmap->size_x; j++) {
                if (pmap->map[i][j] == curr_road_num) {
                    int dx[] = {1, 0, -1, 0};
                    int dy[] = {0, 1, 0, -1};
                    
                    for (int k = 0; k < 4; k++) {
                        int next_i = i + dy[k];
                        int next_j = j + dx[k];
                        
                        if (next_i >= 0 && next_i < pmap->size_y && next_j >= 0 && next_j < pmap->size_x) {
                            if (!pmap->map[next_i][next_j]) {
                                pmap->map[next_i][next_j] = curr_road_num + 1;
                                found = 1;
                                
                                if (next_j == end_point_x && next_i == end_point_y) {
                                    run = 0;
                                    run_2 = 0;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        if(!found){
            *errored = 1;
            break;
        }
        curr_road_num++;
        run_2=1;
    }
}


void select_map(proceed_map* pmap){
    int end_point_x; 
    int end_point_y;
    int run=1;
    int run_2=1;
    if(pmap->exit_x_y[1]==pmap->size_x-1){
        end_point_x=pmap->size_x-2;
        end_point_y=pmap->exit_x_y[0];
    }
    else if (pmap->exit_x_y[0]==pmap->size_y-1){
        end_point_x=pmap->exit_x_y[1];
        end_point_y=pmap->size_y-2;
    }
    int desc_num = pmap->map[end_point_y][end_point_x]-1;
    pmap->map[end_point_y][end_point_x]=-3;
    while(run){
        for(int i=0; i<pmap->size_y && run_2; i++){
            for(int j=0; j<pmap->size_x; j++){
                if(pmap->map[end_point_y-1][end_point_x]==desc_num){
                    pmap->map[end_point_y-1][end_point_x]=-3;
                    end_point_y--;
                    run_2=0;
                    if(desc_num==2) run=0;
                    break;
                }
                else if(pmap->map[end_point_y][end_point_x-1]==desc_num){
                    pmap->map[end_point_y][end_point_x-1]=-3;
                    end_point_x--;
                    run_2=0;
                    if(desc_num==2) run=0;
                    break;
                }
                else if(pmap->map[end_point_y][end_point_x+1]==desc_num){
                    pmap->map[end_point_y][end_point_x+1]=-3;
                    end_point_x++;
                    run_2=0;
                    if(desc_num==2) run=0;
                    break;
                }
                else if(pmap->map[end_point_y+1][end_point_x]==desc_num){
                    pmap->map[end_point_y+1][end_point_x]=-3;
                    end_point_y++;
                    if(desc_num==2) run=0;
                    break;
                }
            }
        }
        desc_num--;
        run_2=1;
    }
}

final_map* format_map(proceed_map* pmap){
    final_map* fmap = malloc(sizeof(final_map));
    fmap->map=calloc(pmap->size_y,sizeof(char*));
    fmap->size_x=pmap->size_x;
    fmap->size_y=pmap->size_y;
    fmap->steps=0;
    for(int i=0; i<fmap->size_y; i++){
        fmap->map[i]= (char*)calloc(fmap->size_x+1,sizeof(char));
    }
    for(int i=0; i<fmap->size_y; i++){
        for(int j=0; j<fmap->size_x; j++){
            if(pmap->map[i][j]==-3){
                fmap->map[i][j]='o';
                fmap->steps++;
            }
            else if(pmap->map[i][j]==1){
                fmap->map[i][j]='*';
            }
            else if(pmap->map[i][j]==-1){
                fmap->map[i][j]='1';
            }
            else if(pmap->map[i][j]==-2){
                fmap->map[i][j]='2';
            }
            else{
                fmap->map[i][j]=' ';
            }
        }
    }
    return fmap;
}

void print_map(final_map* fmap){
    printf("%dx%d* o12\n",fmap->size_y,fmap->size_x);
    for(int i=0; i<fmap->size_y; i++){
        printf("%s\n",fmap->map[i]);
    }
    printf("%d STEPS!\n",fmap->steps);
}