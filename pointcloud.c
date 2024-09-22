#include <stdio.h>
#include "pointcloud.h"
#include "util.h"

/**
 * @author Sara Theriault
 * Com S 3270
 */

int main()
{   
   stat1();

    return 0;
}

/**
 *  Reads a point cloud stream until the end, and prints out the
 *  height and grid location of the minimum height & maximum height.
 *  It should also print out the average height of all data points
 *  No return type 
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
 * Reads point cloud data from steam and
 * stores each point an expanding list
 */
readPointCloudData(FILE *stream, int *rosterWidth, List* pc)
{
    //FIXME: ADD

}

/**
 * 
 */
void imagePointCloud(List *l, char *fileName)
{

}