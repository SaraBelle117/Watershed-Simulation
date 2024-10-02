#ifndef POINTCLOUD_H
#define POINTCLOUD_H

void stat1(); 
PointCloudStats stat2(List *l);

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



#endif