#ifndef POINTCLOUD_H
#define POINTCLOUD_H

void stat1(); 

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



#endif