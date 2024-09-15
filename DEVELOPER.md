# Project 1 - COM S 3270
By Sara Theriault

## Table of Contents
1. [Overview](#overview)
2. [Project Structure](#project-structure)
3. [Setup for Development](#setup-for-development)
4. [Building the Project](#building-the-project)
5. [Testing](#testing)


## Overview
This program will simulate water flow over a terrain when it rains. The purposes of this assignment are to practice writing a program in C language, and also help indicate where water is most likely to pool in a given area. The data comes from LIDAR for the land height at 1 meter resolution. This program is mainly intended for education purposes and is part of the course COM S 327 at Iowa State University. 

## Project Structure
So far, the pointcloud.c file contains the function stat which is part of the main branch. The header file pointcloud.h includes the prototype for the stat1 function, and the makefile ensures that stat1 is always run through pointcloud.c. 

## Setup for Development
This project was made using Visual Studio Code and GitLab. A personal access token was necessary to clone my repo in VS code as well as Pyrite. I was able to run my code in Pyrite using a personal access token and the following line of code (for future reference): ssh sarab117@pyrite-n4.cs.iastate.edu --> I used -v and -vvv to help debug when this didn't work at first. The -n4 was a suggestion from one of the TAs given in Piazza. 

## Building the Project
The first part of the project

## Testing
So far, testing is used with a array that is in the main function in pointcloud.c. I used the files test.xyz, test1.xyz, and test2.xyz to verify that my code is working so far. 

