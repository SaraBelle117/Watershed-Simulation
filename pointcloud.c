#include <stdio.h>
#include <stdlib.h>
#include "pointcloud.h"
#include "util.h"
#include "bmp.h"

/**
 * @author Sara Theriault
 * Com S 3270
 */


/**
 *  Reads a point cloud stream until the end, and prints out the
 *  height and grid location of the minimum height & maximum height.
 *  It should also print out the average height of all data points
 *  @return void (no return type)
*/
void stat1()
{
    double x, y, height;
    double min, max, avgHeight = 0, minX = 0, minY = 0, maxX = 0, maxY = 0;
    int row = 0;

    //will execute as long as stdin has 3 floating point numbers 
    while(scanf("%lf %lf %lf", &x, &y, &height) == 3){
        //tracking # of rows 
        row++;
            if(row == 1){
                //ensures minimum is a valid height given the data
                min = height;
                max = height;
            }
            if(min > height){
                min = height;
                minX = x;
                minY = y;
            }
            else if(max < height){
                max = height;
                maxX = x;
                maxY = y;
            }
        avgHeight += height;
    }
    //divides the sum of all avg height by the number of heights given
    if(row != 0){
        avgHeight /= row;
    }
    else 
    {
        printf("Error. No data found.");
    }

    printf("\n~~~ Printing Stat1 ~~~");
    printf("\nMaximum height: %lf\nAt (x: %lf, y: %lf)\n", max, maxX, maxY);
    printf("Minimum height: %lf\nAt (x: %lf, y: %lf)\n", min, minX, minY);
    printf("Average height: %lf\n\n", avgHeight);

}

/**
 * stat function for imagePointCloud
 * @param pointer to list
 * @return stats for pointcloud data
 */
PointCloudStats stat2(List *l)
{
    PointCloudStats stats;
    pcd_t* setVal = listGet(l, 0);
    stats.min = *setVal;
    stats.max = *setVal;
    for(int i = 0; i < l->size; i++){
        pcd_t* temp = listGet(l, i);
        
        if(temp->z > stats.max.z){
            stats.max = *temp;
        }
        else if(temp->z < stats.min.z){
            stats.min = *temp;
        }
    }
    return stats;
}

/**
 * Reads point cloud data from steam and
 * stores each point an expanding list
 * @param file input stream, size of list, and pointer to list
 * @return void (no return type)
 */
void readPointCloudData(FILE *stream, int *rasterWidth, List *pc)
{
    if(!stream || !rasterWidth || !pc){
        fprintf(stderr, "Error with input parameters.\n");
        exit(-1);
    }
        
    if(*rasterWidth <= 0){
        fprintf(stderr, "Error! Rasterwidth ain't right: %d\n", *rasterWidth);
        exit(-1);
    }

    pcd_t pts;
    int maxSize = (*rasterWidth) * (*rasterWidth);

    if(listInit(pc, maxSize, sizeof(pcd_t))!= 0){
        fprintf(stderr, "List not intialized.\n");
        exit(-1);
    }

    while(fscanf(stream,"%lf %lf %lf", &pts.x, &pts.y, &pts.z)==3){
            listAddEnd(pc, &pts);
            //printf("Points added: %lf %lf %lf\n", pts.x, pts.y, pts.z);
    }
    //fclose(stream);
}

/**
 * Function that creates a gif image of the point-cloud 
 * data
 * @param pointer to list, width, and file name
 * @return void (no return type)
 * Divide the range of heights into 256 equal lengths
 * Assign heights in the lowest range to black (0, 0, 0)
 * Assign heights in the largest range to white (255, 255, 255)
 * Heights in other ranges are distributed proportionally
 * 
 */
void imagePointCloud(List *l, int width, char *fileName)
{
    Bitmap *b = bm_create(width, width);
    PointCloudStats stats = stat2(l);
    double range = stats.max.z - stats.min.z;

    if(range <= 0){
        fprintf(stderr, "Invalid: Range is less than or equal to zero.\n");
        exit(-1);
    }

    printf("Range: %lf,  width: %d\n", range, width);
    for(int i = 0; i < l->size; i++){
        pcd_t* temp = listGet(l, i);
        //printf("%lf %lf %lf\n", temp->x, temp->y, temp->z);
        if(!temp){
            fprintf(stderr, "Null pointer at index %d\n", i);
            continue;
        }
        //skip invalid points
        if((int)temp->z <= 0){
            continue; 
        }
        int grayScale = (((int)temp->z - stats.min.z)/range)*255;
        int hexVal = ((grayScale << 24)|(grayScale << 16)|(grayScale <<8)|grayScale);
        char hex[9];
        sprintf(hex, "%08X", hexVal);
        //printf("Hex: %s Grayscale: %d, Putting points x:  %d, y: %d\n", hex, grayScale, (int)temp->x,(int)temp->y);
        bm_set_color(b, bm_atoi(hex));
        //bm_set_color(b, bm_atoi("pink"));
        bm_putpixel(b,(int)temp->x, (int)temp->y);
    }
    printf("Saving bitmap to out.gif!\n");
    bm_save(b, fileName);
    bm_free(b);
}