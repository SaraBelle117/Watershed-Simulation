#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pointcloud.h"
#include "util.h"
#include "bmp.h"

/**
 * @author Sara Theriault
 * Com S 3270
 */

void stat1()
{
    double x, y, height;
    double min, max, avgHeight = 0, minX = 0, minY = 0, maxX = 0, maxY = 0;
    int row = 0;
    int width = 0;
    //dummy value to make sure we don't read the first line in the texts as stats
    scanf("%d", &width);

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
 * Calculates min/max for x, y, & z vals
 * @param pointcloud_t* l
 * @return stats for pointcloud data
 */
stats stat2(pointcloud_t* l)
{
    stats point;
    pcd_t* setVal = listGet(&l->points, 0);
    //ensures we got a valid point from the list 
    if(!setVal){
        fprintf(stderr, "Failed to get index 0 from list.\n");
        exit(-1);
    }

    //sets min & max to values at list[0]
    point.min = *setVal;
    point.max = *setVal;

    //iterate through the list starting at position one
    for(int i = 1; i < l->points.size; i++){
        pcd_t* position = listGet(&l->points, i);
        //making sure temp is not null before contuining
        if(!position){
            fprintf(stderr, "Null pointer at index %d\n", i);
            continue;
        }

        //sets max and min for z
        point.max.z = MAX(point.max.z, position->z);
        point.min.z = MIN(point.min.z, position->z);

        //sets max and min for x
        point.min.x = MIN(point.min.x, position->x);
        point.max.x = MAX(point.max.x, position->x);

        //sets max and min for y
        point.min.y = MIN(point.min.y, position->y);
        point.max.y = MAX(point.max.y, position->y);
    }

    //ensures stats min is not negative (bug fix)
    if(point.min.z < 0){
        point.min.z = 0;
    }
    return point;
}

/**
 * Reads point cloud data from stream and
 * stores each point an expanding list
 * @param file input stream, size of list, and pointer to list
 * @return void (no return type)
 */
pointcloud_t *readPointCloudData(FILE *stream, List* pc)
{   
    pointcloud_t *l = malloc(sizeof(pointcloud_t));

    if(!l){
        fprintf(stderr, "l is null\n");
        exit(-1);
    }

    int rasterWidth = 0;

    //checks that the parameters are not null
    if(!stream){
        fprintf(stderr, "Error with input parameters.\n");
        exit(-1);
    }

    fscanf(stream, "%d", &rasterWidth);

    //makes sure rasterWidth is a valid num
    if(rasterWidth <= 0){
        fprintf(stderr, "Rasterwidth must be positive, cannot be: %d\n", rasterWidth);
        exit(-1);
    }

    pcd_t pts;
    int maxSize = (rasterWidth) * (rasterWidth);

    //make sure list is initalized
    if(listInit(pc, maxSize, sizeof(pcd_t)) != 0){
        fprintf(stderr, "List not initialized\n");
        free(l);
        exit(-1);
    }

    //reads the points
    while(fscanf(stream,"%lf %lf %lf", &pts.x, &pts.y, &pts.z) == 3){
            listAddEnd(pc, &pts);
    }

    l->rows = rasterWidth;
    l->cols = rasterWidth;
    l->points = *pc;

    return l;
}

/**
 * Creates a gif image of the point-cloud data
 * @param pointer to list, width, and file name
 * @return void 
 */
void imagePointCloud(pointcloud_t *l, char *fileName)
{
    if(!l->points.data){
        fprintf(stderr, "L IS NULL!\n");
        exit(-1);
    }

    Bitmap *b = bm_create(l->rows, l->cols);
    if(!b){
        fprintf(stderr, "Bitmap FAIL\n");
        exit(-1);
    }

    stats point = stat2(l);
    double range = point.max.z - point.min.z;
    
    //ensures range is a valid num
    if(range <= 0){
        fprintf(stderr, "Invalid: Range is less than or equal to zero.\n");
        exit(-1);
    }

    for(int i = 0; i < l->points.size; i++){
        pcd_t* temp = listGet(&l->points, i);

        //making sure temp is not null before contuining
        if(!temp){
            fprintf(stderr, "Null pointer at index %d\n", i);
            continue;
        }
        
        int x, y;
        //normalizes (scales) x & y points 
        x = (int)round(((temp->x - point.min.x)/(point.max.x - point.min.x))* (l->rows - 1));
        y = (int)round(((temp->y - point.min.y)/(point.max.y - point.min.y))* (l->cols - 1));

        //skip invalid points
        if((int)temp->z < 0 || x < 0 || x >= l->rows || y < 0 || y >= l->cols){
            continue; 
        }

        int grayScale; 
        //calculates grayScale val
        grayScale = (int)(((temp->z - point.min.z) / range) * 255.0);
     
        //ensures grayScale is a valid #
        if(grayScale < 0) grayScale = 0;
        if(grayScale > 255) grayScale = 255;
        
        //sets pixels of the bitmap & adds them to it
        bm_set_color(b, bm_rgb(grayScale, grayScale, grayScale));
        bm_putpixel(b, x, y);
    }

    if(!b){
        fprintf(stderr, "Failed to rotate bitmap.\n");
        return;
    }

    bm_save(b, fileName);
    bm_free(b);
}

/**
 * Sets amount of water in each location to zero
 * set the north, south, east, and west pointers 
 * to points to the cell/points that are directly
 * north, south, east, and west of each point
 * @param pointcloud_t* l 
 * @return 0 if succeeded, or -1 if not
 */
int initializeWater(pointcloud_t *l)
{
    //to use for error checking at the end 
    stats p_stats = stat2(l);

    //for error checking
    pcd_t *southwest = NULL;
    pcd_t *northeast = NULL;

    //create 1D array to hold the list of vals 
    pcd_t **arr = calloc((l->rows * l->cols), sizeof(pcd_t));

    if(!arr){
        fprintf(stderr, "Array not allocated in intializeWater.\n");
        return -1;
    }

    for(int i = 0; i < l->points.size; i++){
        pcd_t *position = listGet(&l->points, i);
        //making sure temp is not null before contuining
        if(!position){
            fprintf(stderr, "Null pointer at index %d\n", i);
            continue;
        }

        //set all water levels to zero
        position->wd = 0;

        //set all pointers initially to null
        position->north = NULL;
        position->south = NULL;
        position->east = NULL;
        position->west = NULL;
    
        //sets the found min x & y values to southwest
        if(position->x == p_stats.min.x && position->y == p_stats.min.y ) southwest = position;

        //sets the found max x & y values to northeast
        if(position->x == p_stats.max.x && position->y == p_stats.max.y) northeast = position;

        //convert each point into x & y values (aka scaling/normalizing values)
        int x = normalize(position->x, p_stats.min.x, p_stats.max.x, l->rows);
        int y = normalize(position->y, p_stats.min.y, p_stats.max.y, l->cols);

        //sets the point in the corresponding point in 1D array
        arr[INDEX(y, x, l->cols)] = position;
    }


    for(int y = 0; y < l->rows; y++){
        for(int x = 0; x < l->cols; x++){
            pcd_t* pos = arr[INDEX(y, x, l->cols)];
            //if not a valid position (null or otherwise), go to next point
            if(!pos) continue; 

            //updates north neighbor (if not in the first row)
            if(y > 0) pos->north = arr[INDEX((y - 1), x, l->cols)];
            else pos->north = NULL;

            //updates south neighbor (if not in the last row)
            if(y < l->rows - 1) pos->south = arr[INDEX((y + 1), x, l->cols)];
            else pos->south = NULL;

            //updates east neighbor (if not in last col)
            if(x < l->cols - 1) pos->east = arr[INDEX(y, (x + 1), l->cols)];
            else pos->east = NULL;

            //updates west neighbor (if not in first col)
            if(x > 0) pos->west = arr[INDEX(y, (x - 1), l->cols)];
            else pos->west = NULL;

        }
    }

    //check that min x & y is the most southwest point, and that max x & y is the most northeast point
    if(!northeast || !southwest){
        fprintf(stderr, "Northeast and southwest NULL.\n");
        return -1;
    }
    //checks that northeast points are as expected
    if(northeast->north){
       printf("Error with northeast north neighbor, x: %f, y: %f\n", northeast->north->x, northeast->north->y);
       return -1;
    }
    if(northeast->east){
        printf("Error with northeast north neighbor, x: %f, y: %f\n", northeast->east->x, northeast->east->y);
       return -1;
    }
    //checks that southeast points are as expected
    if(southwest->south || southwest->west){
        printf("Error with southeast point (south != null || west != null)\n");
        return -1;
    }

    free(arr);
    return 0;
}

/**
 * Adds uniform amount of water to pointcloud
 * @param pointcloud_t* list
 * @param double amount of water
 */
void watershedAddUniformWater(pointcloud_t* l, double amount)
{
    for(int i = 0; i < l->points.size; i++){
        pcd_t* position = listGet(&l->points, i);
        //if not a valid position (null or otherwise), go to next point
        if(!position)continue;
        position->wd = amount;
    }
}

/**
 * Computes one time step of the iteration
 * @param pointcloud_t* l 
 * @return void
 */
void watershedStep(pointcloud_t* l)
{
    for(int i = 0; i < l->points.size; i++){
        pcd_t* pos = listGet(&l->points, i);
        //if not a valid position (null or otherwise), go to next point
        if(!pos) continue;

        //if north neighbor is null, set water amount to 0, else calculate waterflow in north dir
        if(!pos->north){
            pos->northflow = 0;   
        }
        else{
            pos->northflow = f(pos->z, pos->wd, pos->north->z, pos->north->wd, l->wcoef);
        }

        //if south neighbor is null, set water amount to 0, else calculate waterflow in south dir
        if(!pos->south){
            pos->southflow = 0;
        } 
        else{
            pos->southflow = f(pos->z, pos->wd, pos->south->z, pos->south->wd, l->wcoef);
        }

        //if east neighbor is null, set water amount to 0, else calculate waterflow in east dir
        if(!pos->east){
            pos->eastflow = 0;
        }
        else{
            pos->eastflow = f(pos->z, pos->wd, pos->east->z, pos->east->wd, l->wcoef);
        }

        //if west neighbor is null, set water amount to 0, else calculate waterflow in west dir
        if(!pos->west){
            pos->westflow = 0;
        } 
        else{
            pos->westflow = f(pos->z, pos->wd, pos->west->z, pos->west->wd, l->wcoef);
        }
        //adds all the flows in each direction (minus current * evaporation coeff) to position's water amount
        pos->wd += (pos->eastflow + pos->northflow + pos->southflow + pos->westflow) - (pos->wd * l->ecoef);

        //ensures water depth is a valid number (greater than zero, less than or equal to max water depth)
        if(pos->wd < 0) pos->wd = 0;
        if(pos->wd > l->maxwd) pos->wd = l->maxwd;
    }
}

/**
 * Calculates difference of amount of water and height
 * scaled by the water coefficient
 * f(pos->z, pos->wd, pos->dir->z, pos->dir->wd) 
 * (pos->dir->z + pos->dir->wd) − (pos->z + pos->wd) ∗ 𝑤𝑐𝑜𝑒𝑓
 * @param elevation of cell
 * @param water depth of cell
 * @param neighbor's elevation
 * @param neighbor's water depth
 * @param water coefficient (given value)
 * @return double value of the calculated water depth 
 */
double f(double pos_z, double pos_wd, double dir_z, double dir_wd, double wcoef)
{  
    //added * pos_wd to ensure no water comes from no where (per professor's suggestion in Piazza)
    return (((dir_z + dir_wd) - (pos_z + pos_wd)) * wcoef) * pos_wd;
}

/**
 * Converts a given point into a given index
 * @param point (x or y)
 * @param min value of given value
 * @param max value of given value
 * @param index (rows if x, cols if y)
 * @return int normalized/scaled value
 */
int normalize(double point, double  min, double max, int index){
    //fixes issue with max point 
    if(point == max) return (index - 1);
    //fixes issue with division by zero
    if(max == min) return 0; 
    return (int)((point - min)/(max - min)) * (index - 1);
}

/**
 * Creates a gif image of the water at that point
 * @param pointcloud_t* l 
 * @param maxwd max water depth
 * @param char* file name
 */
void imagePointCloudWater(pointcloud_t* l, double maxwd, char* filename)
{
    //checks that l is null
    if(!l->points.data){
        fprintf(stderr, "L IS NULL!\n");
        exit(-1);
    }
    //creates the bitmap
    Bitmap *b = bm_create(l->rows, l->cols);
    if(!b){
        fprintf(stderr, "Bitmap FAIL\n");
        exit(-1);
    }
    //for grayScale values (and normalization of the points)
    stats st = stat2(l);
    double range = st.max.z - st.min.z;

    for(int i = 0; i < l->points.size; i++){
        pcd_t* position = listGet(&l->points, i);
        //if not a valid position (null or otherwise), go to next point
        if(!position) continue;

        //normalizes (scales) x & y points (ended up not using normalize function due to rounding issues)
        int x = (int)round(((position->x - st.min.x)/(st.max.x - st.min.x))* (l->rows - 1));
        int y = (int)round(((position->y - st.min.y)/(st.max.y - st.min.y))* (l->cols - 1));
      
        int grayscale, bluescale; 
        //calculates blue scale val
        bluescale = (position->wd / maxwd) * 255;
        //calculates grayScale val
        grayscale = (int)(((position->z - st.min.z) / range) * 255.0);

        //ensures grayscale is a valid #
        if(grayscale < 0) grayscale = 0;
        if(grayscale > 255) grayscale = 255;
        //ensures bluescale is a valid # 
        if(bluescale > 255) bluescale = 255;
    
        //mainly for aesthetic purposes (trying to make sure bluescale doesn't get to 0)
        if(position->wd <= 0 || bluescale <= 0){
            bluescale = grayscale;
        }
        

        bm_set_color(b, bm_rgb(grayscale, grayscale, bluescale));
        bm_putpixel(b, x, y);
    }

    bm_save(b, filename);
    bm_free(b);

}