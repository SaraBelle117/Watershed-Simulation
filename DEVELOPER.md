# Project 1 - COM S 3270
By Sara Theriault
Com S 3270
Fall 2024

## Table of Contents
1. [Overview](#overview)
2. [Project Structure](#project-structure)
3. [Setup for Development](#setup-for-development)
4. [Challenges Encountered](#challenges-encountered)
5. [Testing](#testing)


## Overview
This program will simulate water flow over a terrain when it rains. The purposes of this assignment are to practice writing a program in C language, and also help indicate where water is most likely to pool in a given area. The data comes from LIDAR for the land height at 1 meter resolution. This program is mainly intended for education purposes and is part of the course COM S 327 at Iowa State University. Part a implemented a simple stat function which outputs the min/max values for z (the height), as well as the x & y values for those points. Part b took those same points, and output a gif file using the stats calculated in part a. However, it was necessary to also save the min and max x & y values, which differed from part a. Memory was managed using an "ArrayList" (just like in Java), so the list structure would double in size anytime the maximum size was reached. Part c also creates a bitmap (viewed as a .gif file) but allows the user to specify the conditions of initial water depth, the iterations (of the calculation for water amount), the water and evaporation coefficient, and how many .gif files will be output. The result is a series (or just 1) .gif image which simulates the movement of water given the elevation of the terrain.

## Project Structure
parta.c: Contains the call for the stat(...) function for part a so it can be graded separately. 
util.h: Contains the list structure and corresponding prototypes, as well as the macro to convert from a 2D array to a 1D array. 
util.c: Contains the functions to allocate space for the array list, initialize the list, add an element to the end of the list (and double the size if the list is full), and retrieve an element in the list by index. 
pointcloud.h: Contains the pcd_t structure (used for the points), and PointCloudStats which are used for the stat2(...) function (and later utilized in imagePointCloud). 
pointcloud.c: Contains the contents of stat1(), stat2(...), readPointCloudData(...), and imagePointCloud(...). This is how the points are being read in, and saved in the corresponding list structure. Additionally, the bitmap is also generated inside of this file. Additionally, this file contains all the functions necessary in watershed.c. Notable calculations include f(...) which is the calculation for the change in water amount (at a given position). Additionally, I added a normalize(...) function since I had used this in various parts of my code. Ultimately, I couldn't figure out a way to use this in all the spots that have a very similar calculation due to needing round(..) before casting as an int (as the normalize function returns an int but the calculation would be a double value). 
display.c: This is the file that reads the command line arguments and calls the functions to read the data, then output to out.gif. This was implemented in part b. 
watershed.c: This is the file that does the same as part b but with the added water simulation. 

## Setup for Development
This project was made using Visual Studio Code and GitLab. A personal access token was necessary to clone my repo in VS code as well as Pyrite. I was able to run my code in Pyrite using a personal access token and the following line of code (for future reference): ssh sarab117@pyrite-n4.cs.iastate.edu --> I used -v and -vvv to help debug when this didn't work at first. The -n4 was a suggestion from one of the TAs given in Piazza. For debugging, I used lldb, or simple printf statements which will be deleted by the time the project is turned in. 

To run the program, use: ./watershed <ifile> <iter> <iwater> <wcoef> <ecoef> <ofilebase> <maxwdepth> <seq>

Note that wcoef must be between 0 and 0.2 and ecoef must be between 0 and 0.9. I also checked that iwater was negative, since I didn't know what would happen if that were the case, and I did not intend on finding out.

## Challenges Encountered
Once the list was allocating memory for the points correctly, finding a way to correctly normalize the x & y points was one of the hardest portions I came across. I had a very persistent bug which caused black pixels across the screen (vertically and horizontally), and this bug only went away once I decided to try using a cast to an int after I rounded the data ((int)round(...)). 

A big barrier was how to shade the map -- and I went with a very similar approach (if not identical) to how I did this in part b. The big difference was that instead of only populating using my grayscale calculation, the red/green values were grayscale, and the blue values were determined by bluescale. The instructions in the homework document said "you may research how to shade a map" were quite vague but at least implied that we would not be graded too harshly on that portion. Honestly, I never was able to get the shading how I wanted (I couldn't find a way to shade online, so I did my own implementation which may have been less ...visually pleasing). The map is just very yellow. If I had more time with the project, I would have spent more time scaling each value (since yellow means 0 bluescale value). I have some comments in my code that also allude to this frustration.

Normalizing/scaling the points was also a challenge in both part a and b. I implemented a "normalize" function, and only ended up using this is the initializeWatershed(...) function which was not my original intention. I even attempted to change normalize to return a double, and then cast to an int after I used round(...), ceil(...), or floor(...), but niether options ended up with the results I was hoping for. In the end, I cut my losses and just used it the one time in my code. In general, I used ((point - min)/(max - min)) * (index - 1). To be candid, my partner (not a CS major, but statistics phd student, so adjacent) helped me with this formula (since my ideas weren't working, or would skew data very easily).

A HUGE barrier I found early in implementing part C was the runtime complexity of the initializeWatershed(...) function. Initially, this function was O(n^2), which was NOT ideal given the size of data. Running test.xyz was taking SO long, so I tried some "tricks" to make it go faster. I made the assumption (originally) that the points nearby would be nearby (so I only iterated within 50 points of each position... not my best work), but then I later decided that wasn't an assumption I was comfortable making. I also hadn't implemented use of the INDEX(...) macro yet, so to kill two birds with one stone, I ended up using a 2D array (**arr) to hold the values using this macro. So I only had to iterate through the list to initialize/populate the amount of water -- which was O(n) -- and then I iterate through the list, and at each point, I can directly check the North, South, East, & West neighbors using INDEX(...). The runtime complexity for the second (nested) for loop is O(l->rows * l->cols). So the total runtime complexity ended up being O(n + l->rows * l->cols), which simplifies to O(n). Overall, I enjoyed this part of the project a lot! 

## Testing
Files used to test: test.xyz, test1.xyz, test2.xyz, test3.xyz, test4.xyz, test5.xyz, and a few other test cases provided from another student in Piazza. When I ran into the pixel issue (mentioned above), I also used bm_atoi("pink") to get a better visual of when the issue occurs, which helped me narrow down that the issue was in the x & y coordinates (and not the greyScale calculation as it would appear). This is something I used again periodically to test the water depth as well. 

To be candid, the majority of testing was done with print statements and checking the bitmaps. I checked basically every possible given value (with each test file) to ensure values were expected. I also have a lot of error checking in my code that (hopefully) ensures that unexpected results are avoided. Nonetheless, there is always the chance that I missed something.