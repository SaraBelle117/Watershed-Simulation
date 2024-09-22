#include <stdio.h>
#include <stdlib.h>
#include "util.h"

/**
 * allocate space for a 2D array &
 * initializes all elements to zero
 */
void *allocateArray(int rows, int columns){
    return (double*)calloc((rows * columns), rows * columns* sizeof(double));
}

/**
 * initializes a List structure with data
 * to create an empty list & sets its
 * capacity 
 * default max size = 10
 */
int listInit(List* l, int max_element_size){
    l->max_size = 10; //default max size = 10
    l->max_element_size = max_element_size; //setting capacity
    l->size = 0; //current list is empty
    l->data = allocateArray(l->max_size, l->max_element_size);

    return 0;
}

/**
 * adds an element to the end of the list
 * doubles the size of the list if the list is
 * full
 */
void listAddEnd(List* l, void* elmt){
    if(l->size >= l->max_size){
        int double_size = l->max_size * 2;
        void *arr = malloc((double_size)* l->max_element_size);
        memcpy(arr, l->data, (l->size * l->max_element_size));
        free(l->data);
        l->data = arr;
        l->max_size = double_size;
    }

    memcpy(elmt, l->max_element_size);
    l->size++; //added element, so size is increased
}

/**
 * returns a pointer to the data in the
 * list 
 * (retrieves an element in the list by
 * index)
 */
void *listGet(List* l, int index){
   return l->data;
}