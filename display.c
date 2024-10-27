#include <stdio.h>
#include <stdlib.h>
#include "pointcloud.h"
#include "util.h"

int main(int argc, char *argv[])
{

    FILE* ptr;
    if(argc == 2){
        ptr = fopen(argv[1], "r");
        if(!ptr){
            fprintf(stderr, "Could not open file.\n");
            exit(-1);
        }
    }
    else if(argc == 1){
        ptr = stdin;
    }
    else{
        fprintf(stderr, "Invalid argument! Argc cannot be %d\n", argc);
        exit(-1);
    }


    List* l = malloc(sizeof(List));
    if(!l){
        fprintf(stderr, "Could not allocate memory for list.\n");
        exit(-1);
    }

    pointcloud_t *lp = readPointCloudData(ptr, l);

    if(!lp){
        fprintf(stderr,"failed to read pointcloud data\n");
        free(lp);
        exit(-1);
    }

    if(ptr != stdin){
        fclose(ptr);
    }

    imagePointCloud(lp, "out.gif");

    if(l->data){
        free(l->data);
    }

    free(l);
    free(lp);

    printf("Bitmap completed. Check out.gif for result.\n");

    return 0;
}