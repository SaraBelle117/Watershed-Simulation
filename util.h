#ifndef UTIL_H
#define UTIL_H
#define INDEX(row, col, numCol) ((row)*(numCol)+(col))

typedef struct 
{   
    int max_size;   //max possible size of list
    int max_element_size; //max size of element in array
    void* data;
    int size;
}List;

int listInit(List* l, int max_element_size);
void listAddEnd(List* l, void* elmt);
void *listGet(List* l, int index);
void *allocateArray(int rows, int columns);

#endif UTIL_H



