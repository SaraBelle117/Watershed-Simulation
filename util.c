#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "util.h"
#include "pointcloud.h"

/**
 * allocate space for a 2D array &
 * initializes all elements to zero
 * @param int rows
 * @param int columns
 */
void *allocateArray(int rows, int columns)
{
    void* arr = calloc((rows * columns), sizeof(pcd_t));

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
 * capacity -- default max size = 10
 * @param List* list 
 * @param int maximum size of list
 * @param max_element_size maximum data size (bytes)
 */
int listInit(List* l, int max_size, int max_element_size)
{
    l->max_size = max_size; 
    //setting capacity
    l->max_element_size = max_element_size;
    //cureent list is empty
    l->size = 0; 
    //allocates data for array 
    l->data = allocateArray(l->max_size, l->max_element_size);

    //ensuring memory allocation was successful
    if(!l->data){
        fprintf(stderr, "Failed to allocate memory for the list.\n");
        exit(-1);
    }
    return 0;
}

/**
 * Adds an element to the end of the list & 
 * doubles the size of the list if the list is full
 * @param List* l
 * @param void* element to add
 */
void listAddEnd(List* l, void* elmt)
{
    //error checking for if l or element is null
    if(!l || !elmt){
        fprintf(stderr, "List or element is NULL!\n");
        exit(-1);
    }

    if(l->size >= l->max_size){
        //doubles the size 
        int double_size = l->max_size * 2;
        //rellocates memory with new size 
        void *arr = realloc(l->data, double_size * l->max_element_size);

        if(!arr){
            fprintf(stderr, "Oh no! Arr was not rellocated!");
            exit(-1);
        }

        l->data = arr;
        l->max_size = double_size;
    }

    memcpy((char*)l->data + (l->size * l->max_element_size), elmt, l->max_element_size);
    l->size++; //added element, so size is increased
}

/**
 * Retrieves an element in the list by index
 * @returns a pointer to the data in the list 
 * @returns void pointer --> to where the data is in the list
 */
void *listGet(List* l, int index)
{
    //ensures l is not null
    if(!l || !l->data){
        fprintf(stderr, "List is NULL! Uh-oh!\n");
        return NULL;
    }
    
    //bug fixes, makes sure index is a valid num
    if(index < 0 || index >= (int)l->size){
        fprintf(stderr, "Index %d is out of bounds for size %d. :(\n", index, (int)l->size);
        return NULL;
    }
    
    //(char*) to ensure pointer arithmetic is done in bytes
    //returns the index (accounting for bytes in memory, affecting pos)
   return (char*)l->data + (index * l->max_element_size);
}