#ifndef POINTCLOUD_H
#define POINTCLOUD_H
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#include "util.h"

typedef struct pcd_t
{
   double x;
   double y;
   double z; //height
   double wd;
   double northflow;
   double southflow;
   double westflow;
   double eastflow;
   struct pcd_t *north;
   struct pcd_t *south;
   struct pcd_t *west;
   struct pcd_t *east;
}pcd_t;

typedef struct
{
   pcd_t min;
   pcd_t max;
   pcd_t avgHeight;
}stats;

typedef struct 
{ 
   List points; //the points in the pointcloud
   int rows; //the # of rows in the pointcloud
   int cols; //the # of columns in the pointcloud
   stats stat;
   float ecoef;
   float wcoef;
   float maxwd;
}pointcloud_t;

void stat1(); 
stats stat2(pointcloud_t* l);
void imagePointCloud(pointcloud_t *l, char *fileName);
pointcloud_t *readPointCloudData(FILE *stream, List *pc);
int initializeWater(pointcloud_t *);
void watershedAddUniformWater(pointcloud_t* l, double amount);
void watershedStep(pointcloud_t* l);
double f(double pos_z, double pos_wd, double dir_z, double dir_wd, double wcoef);
int normalize(double point, double  min, double max, int index);
void imagePointCloudWater(pointcloud_t* l, double maxwd, char* filename);

#endif