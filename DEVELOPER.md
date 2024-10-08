# Project 1 - COM S 3270
By Sara Theriault

## Table of Contents
1. [Overview](#overview)
2. [Project Structure](#project-structure)
3. [Setup for Development](#setup-for-development)
4. [Challenges Encountered](#challenges-encountered)
5. [Testing](#testing)


## Overview
This program will simulate water flow over a terrain when it rains. The purposes of this assignment are to practice writing a program in C language, and also help indicate where water is most likely to pool in a given area. The data comes from LIDAR for the land height at 1 meter resolution. This program is mainly intended for education purposes and is part of the course COM S 327 at Iowa State University. Part a implemented a simple stat function which outputs the min/max values for z (the height), as well as the x & y values for those points. Part b took those same points, and output a gif file using the stats calculated in part a. However, it was necessary to also save the min and max x & y values, which differed from part a. Memory was managed using an "ArrayList" (just like in Java), so the list structure would double in size anytime the maximum size was reached. 

## Project Structure
parta.c: Contains the call for the stat(...) function for part a so it can be graded separately. 
util.h: Contains the list structure and corresponding prototypes, as well as the macro to convert from a 2D array to a 1D array. 
util.c: Contains the functions to allocate space for the array list, initialize the list, add an element to the end of the list (and double the size if the list is full), and retrieve an element in the list by index. 
pointcloud.h: Contains the pcd_t structure (used for the points), and PointCloudStats which are used for the stat2(...) function (and later utilized in imagePointCloud). 
pointcloud.c: Contains the contents of stat1(), stat2(...), readPointCloudData(...), and imagePointCloud(...). This is how the points are being read in, and saved in the corresponding list structure. Additionally, the bitmap is also generated inside of this file. 
display.c: This is the file that reads the command line arguments and calls the functions to read the data, then output to out.gif. 

## Setup for Development
This project was made using Visual Studio Code and GitLab. A personal access token was necessary to clone my repo in VS code as well as Pyrite. I was able to run my code in Pyrite using a personal access token and the following line of code (for future reference): ssh sarab117@pyrite-n4.cs.iastate.edu --> I used -v and -vvv to help debug when this didn't work at first. The -n4 was a suggestion from one of the TAs given in Piazza. For debugging, I used lldb. 

## Challenges Encountered
Once the list was allocating memory for the points correctly, finding a way to correctly normalize the x & y points was one of the hardest portions I came across. I had a very persistent bug which caused black pixels across the screen (vertically and horizontally), and this bug only went away once I decided to try using a cast to an int after I rounded the data ((int)round(...)). 

## Testing
For testing, I used test.xyz, test1.xyz, test2.xyz, test3.xyz, and a few other test cases kindly provided by peers from this class on Piazza. When I ran into the pixel issue (mentioned above), I also used bm_atoi("pink") to get a better visual of when the issue occurs, which helped me narrow down that the issue was in the x & y coordinates (and not the greyScale calculation as it would appear). 

