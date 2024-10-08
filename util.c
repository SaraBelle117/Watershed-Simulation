#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "pointcloud.h"

/**
 * allocate space for a 2D array &
 * initializes all elements to zero
 */
void *allocateArray(int rows, int columns)
{
    void* arr = calloc((rows * columns), sizeof(double));

    //ensuring the memory was allocated
    if(!arr){
        fprintf(stderr, "Could not allocate memory!\n");
        exit(-1);
    }
    return arr;
}

/**
 * initializes a List structure with data
 * to create an empty list & sets its
 * capacity 
 * default max size = 10
 */
int listInit(List* l, int max_size, int max_element_size)
{
    l->max_size = max_size; 
    l->max_element_size = max_element_size; //setting capacity
    l->size = 0; //current list is empty

    l->data = allocateArray(l->max_size, l->max_element_size);

    //ensuring memory allocation was successful
    if(!l->data){
        fprintf(stderr, "Failed to allocate memory for the list.\n");
        exit(-1);
    }

    return 0;
}

/**
 * adds an element to the end of the list
 * doubles the size of the list if the list is
 * full
 */
void listAddEnd(List* l, void* elmt)
{
    //error checking for if l or element is null
    if(!l || !elmt){
        fprintf(stderr, "List or element is NULL!\n");
        exit(-1);
    }

    if(l->size >= l->max_size){
        int double_size = l->max_size * 2;
        void *arr = malloc(double_size * l->max_element_size);
        
        if(!arr){
            fprintf(stderr, "Oh no! Arr was not rellocated!");
            exit(-1);
        }

        memcpy(arr, l->data, l->size * l->max_element_size);
        free(l->data);
        l->data = arr;
        l->max_size = double_size;
    }

    memcpy((char*)l->data + (l->size * l->max_element_size), elmt, l->max_element_size);
    l->size++; //added element, so size is increased
}

/**
 * returns a pointer to the data in the
 * list 
 * (retrieves an element in the list by
 * index)
 */
void *listGet(List* l, int index)
{
    //ensures l is not null
    if(!l){
        fprintf(stderr, "List is NULL! Uh-oh!\n");
        exit(-1);
    }
    
    //bug fixes, makes sure index is a valid num
    if(index < 0 || index >= (int)l->size){
        fprintf(stderr, "Index %d is out of bounds for size %d. :(\n", index, (int)l->size);
        exit(-1);
    }
    
    //(char*) to ensure pointer arithmetic is done in bytes
   return (char*)l->data + (index * l->max_element_size);
}