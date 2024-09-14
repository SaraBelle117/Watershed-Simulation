#include <stdio.h>

/**
 * @author Sara Theriault
 * Com S 3270
 */


void stat1(double point[][3], int size);

int main()
{
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

    int size = sizeof(point)/sizeof(point[0]);

    stat1(point, size);    

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
    int x = 0;
    int y = 1;
    int height = 2;
    int column = 3; //assuming data points will always be 3 per row
    double min = point[0][height];
    double max;
    double avgHeight;
    int minRow;
    int maxRow;

    for(int i = 0; i < row; i++){
        if(min > point[i][height]){
            min = point[i][height];
            minRow = i;
        }
        else if(max < point[i][height]){
            max = point[i][height];
            maxRow = i;
        }

        avgHeight += point[i][height];
    }

    avgHeight /= 3;

    printf("\nMaximum height: %lf x = %lf, y = %lf\n", max, point[maxRow][x], point[maxRow][x]);
    printf("Minimum height: %lf x = %lf, y = %lf\n", min, point[minRow][x], point[minRow][x]);
    printf("Average height for all data points: %lf\n", avgHeight);

    
}

