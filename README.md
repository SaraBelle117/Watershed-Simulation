# coms3270P1
By Sara Theriault
Com S 3270
Fall 2024

## Project 1:

## Description
This program will simulate water flow over a terrain when it rains. The purposes of this assignment are to practice writing a program in C language, and also help indicate where water is most likely to pool in a given area. The data comes from LIDAR for the land height at 1 meter resolution. Using this program, you can simulate water flow and view the terrain from given data points.

## Features: 
Stat1() function (in pointcloud.c) which prints the minimum, maximum, and average height for the given data points. It also prints the x & y coordinates for the min and max data points. The stat1(...) function does the same thing, but instead of holding the x & y values of the min and max z points, it also will hold the min and max x & y values.

The functions readPointCloudData(...) and imagePointCloud(...) can be used to read the points from the .xyz file and output to a gif file which can be viewed. 

Furthermore, with part c, users can view a simulation of water flow which is calculated by given values (initial water amount, max water depth, water/evaporation coefficients, etc.,). The result is 1 or more gif files which show the water amount in a given spot along a map.

There is a macro for MIN(...), MAX(...) (which work as expected), as well as INDEX(...), which returns an index in 1D form (given as 2D, with the numCols given).


