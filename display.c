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

    int width;
    fscanf(ptr, "%d", &width);

    List lp; 
    if(listInit(&lp, width, sizeof(pcd_t))!= 0){
        fprintf(stderr, "List not initiliazed correctly!\n");
        exit(-1);
    }

    readPointCloudData(ptr, &width, &lp);

    imagePointCloud(&lp, width, "out.gif");

    if(ptr != stdin){
        fclose(ptr);
    }

    free(lp);

    return 0;
}