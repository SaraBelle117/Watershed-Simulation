#include <stdio.h>
#include <stdlib.h>
#include "util.h"

/**
 * allocate space for a 2D array &
 * initializes all elements to zero
 */
void *allocateArray(int rows, int columns){
    double* arr = (double*)calloc((rows * columns), rows * columns* sizeof(double));
}

/**
 * initializes a List structure with data
 * to create an empty list
 * max element size = 10
 */
int listInit(List* l, int max_element_size){
   
}

/**
 * adds an element to the end of the list
 */
void listAddEnd(List* l, void* elmt){

}

/**
 * returns a pointer to the data in the
 * list 
 */
void *listGet(List* l, int index){
    
}