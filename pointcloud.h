#ifndef POINTCLOUD_H
#define POINTCLOUD_H
#include "util.h"

typedef struct
{
   double x;
   double y;
   double z; //height
   double water;
   double *north;
   double *south;
   double *west;
   double *east;
}pcd_t;

typedef struct 
{ //may need to reconfigure so that it is of type pcd_t
   pcd_t min;
   pcd_t max;
   pcd_t avgHeight;
   pcd_t minX, minY;
   pcd_t maxX, maxY;

}PointCloudStats;

void stat1(); 
PointCloudStats stat2(List *l);
void imagePointCloud(List *l, int width, char *fileName);
void readPointCloudData(FILE *stream, int *rasterWidth, List *pc);

#endif