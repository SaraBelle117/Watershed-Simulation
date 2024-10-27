#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pointcloud.h"
#include "util.h"
#include "bmp.h"

int main(int argc, char *argv[]){

    if(argc < 8 || argc > 9){
        fprintf(stderr, "%d is an invalid number of command arguments.\n", argc);
        exit(-1);
    }

    //saves 2nd (after ./watershed) argument as name of file
    char* ifile = argv[1];

    int iter, seq;
    float iwater, wcoef, ecoef, maxwdepth;

    //base filename of the input file
    char *ofilebase = argv[6];
  
    //# of output files (default is 0)
    seq = 0;
    //# of computations
    sscanf(argv[2], "%d", &iter);
    //initial floating point amount of water covering the pointcloud
    sscanf(argv[3], "%f", &iwater);
    //floating point # between 0.0 and 0.2 (water flow coefficient)
    sscanf(argv[4], "%f", &wcoef);
    //floating point # between 0.9 & 1.0 (evaporation coefficient)
    sscanf(argv[5], "%f", &ecoef);
    //max water depth
    sscanf(argv[7], "%f", &maxwdepth);

    if(argc == 9){
        sscanf(argv[8], "%d", &seq);
    }

    //water coefficient must be between 0.0 and 0.2
    if(wcoef < 0.0 || wcoef > 0.2){
        fprintf(stderr, "Water coefficient must be between 0.0 & 0.2, cannot be %f.\n", wcoef);
        exit(-1);
    }

    //evaporation coefficient must be between 0.0001 & 0.9
    if(ecoef > 0.9 || ecoef < 0 ){
        fprintf(stderr, "Evaporation coefficient must be between 0.9 & 1.0, cannot be %f.\n", ecoef);
        exit(-1);
    }


    List* l = malloc(sizeof(List));
    if(!l){
        fprintf(stderr, "Could not allocate memory for list.\n");
        exit(-1);
    }

    //open file for reading
    FILE* fp = fopen(ifile, "r");
    if(!fp){
        fprintf(stderr, "Failed to open file %s.\n", ifile);
        exit(-1);
    }
    //initializes/populates pointcloud_t
    pointcloud_t *lp = readPointCloudData(fp, l);

    if(!lp){
        fprintf(stderr,"failed to read pointcloud data\n");
        free(lp);
        exit(-1);
    }
    //sets values to be used in pointcloud.c
    lp->wcoef = wcoef;
    lp->ecoef = ecoef;
    lp->maxwd = maxwdepth;

    //initializes water amount (uniformly)
    initializeWater(lp);    
    watershedAddUniformWater(lp, iwater);

    //printf("seq: %d\n", seq);
    for(int i = 0; i < iter; i++){
        watershedStep(lp);
        //printf("Completed step %d\n", i);
        for(int j = 0; j < seq; j++){
            //formats file to be filename(index).gif
            //allocates space for index + .gf (and the new filename)
            char indexChar[20];
            sprintf(indexChar, "%d.gif", j);
            char* fileIndex = malloc((strlen(ofilebase) + strlen(indexChar)) *sizeof(char));

            //ensures we allocated space for fileIndex (name of file with /index + .gif)
            if(!fileIndex){
                exit(-1);
                fprintf(stderr, "Failed to allocate memory for filename.\n");
            }
            //copies original file name to new, and then appends index char at the end
            strcpy(fileIndex, ofilebase);
            strcat(fileIndex, indexChar);

            //printf("Making file %d, name: %s\n", j, fileIndex);
            imagePointCloudWater(lp, maxwdepth, fileIndex);
            free(fileIndex);
        }
    }
    //frees list and pointcloud_t 
    free(l);
    free(lp);
    
    return 0;

}