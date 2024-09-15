#include <stdio.h>
#include "pointcloud.h"

/**
 * @author Sara Theriault
 * Com S 3270
 */


//void stat1(double point[][3], int size);

int main()
{   
    /*
    double point[][3] = {
        {445000.5, 4650999.5, 304.95001220703125},
        {445001.5, 4650999.5, 304.95001220703125},
        {445002.5, 4650999.5, 304.959991455078125},
        {445003.5, 4650999.5, 304.94000244140625},
        {445004.5, 4650999.5, 304.94000244140625},
        {445995.5, 4650000.5, 284.209991455078125},
        {445996.5, 4650000.5, 284.220001220703125},
        {445997.5, 4650000.5, 284.260009765625},
        {445998.5, 4650000.5, 284.269989013671875},
        {445999.5, 4650000.5, 284.269989013671875}};
        */
    //for testing purposes ONLY (since file input not yet required)
    double point2[][3] = {
        {12.3, 13.3, 0.5},
        {2.45, 9.534, 2.5},
        {1.2, 3.203, 0.1},
        {2.3, 6.78, 0.25},
        {5.643, 2.323, 0.0},
        {9.23, 10.34, 0.75},
        {8.238, 9.234, 10.0},
        {4.534, 7.84, 0.5},
        {9.23, 1.2, 0.0}};

    int size = sizeof(point2)/sizeof(point2[0]);

    //stat1(point, size);    
    stat1(point2, size);

    return 0;
}

/*
    Reads a point cloud stream until the end, and prints out the
    height and grid location of the minimum height & maximum height.
    It should also print out the average height of all data points
    No return type 
*/
void stat1(double point[][3], int row)
{   
    //using x, y, & height for indexes of each one (for legibility)
    int x = 0;
    int y = 1;
    int height = 2;

    //min, max, and height values to be added in for loop
    double min = point[0][height];
    double max = 0;
    double avgHeight = 0;

    //indexes for min & max values
    int minRow = 0;
    int maxRow = 0;

    for(int i = 0; i < row; i++){
        if(min > point[i][height]){
            min = point[i][height];
            minRow = i;
        }
        else if(max < point[i][height]){
            max = point[i][height];
            maxRow = i;
        }
        //summing all height for avg
        avgHeight += point[i][height];
    }

    //divides the sum of all avg height by the number of heights given
    avgHeight /= row;

    printf("\n~~~ Printing Stat1 ~~~");
    printf("\nMaximum height: %lf\nAt (x: %lf, y: %lf)\n", max, point[maxRow][x], point[maxRow][x]);
    printf("Minimum height: %lf\nAt (x: %lf, y: %lf)\n", min, point[minRow][y], point[minRow][y]);
    printf("Average height: %lf\n\n", avgHeight);
    
}