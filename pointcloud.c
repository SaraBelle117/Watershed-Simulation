#include <stdio.h>
#include "pointcloud.h"
#include "util.h"

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
PointCloudStats stat2(List *l){
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
    //stream = fopen("test.xyz", "r");
    fscanf(stream, "%d", rasterWidth);
    pcd_t pts;
    pc = allocateArray(rasterWidth, rasterWidth);
    listInit(pc, (*(rasterWidth) * *(rasterWidth)));
    while(fscanf(stream,"%lf %lf %lf", &pts.x, &pts.y, &pts.z)==3){
            listAddEnd(pc, &pts);
    }
    fclose(stream);
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
    PointCloudStats stats = stat2(l);

}