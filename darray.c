#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "global.h"
#include "darray.h"
#include "sorting.h"


// Can be redefined if Value_Type changes
// compare two string values
int compare(Value_Type a, Value_Type b){
  return strcmp(a,b);
} // compare

// linear search implemented which search for an element one by one and returns true
// if find it
bool linearSearch(Value_Type value, int size, struct darray* array)
{
  for (int i = 0; i < size; i++)
    if (compare(array->cells[i], value) == 0)
      return true;
  return false;
} // linearSearch

// binary search implemented which search for a given element and returns true if find it
// compare mid by value if mid is less go right if more go to the opposite
bool binarySearch(Value_Type value, struct darray* array, int first, int last)
{
  int mid = 0;
  while (first <= last)
  {
    mid = (last + first)/2;
    if (compare(array->cells[mid], value) == 0)
      return true;
    else if (compare(array->cells[mid], value) < 0)
      first =  mid + 1;
    else
      last = mid - 1;
  } // while
  return false;
} // binarySearch


// initialize which allocate memory for array and cells
// and resets everything to zero
struct darray* initialize_set (int size)
{
  struct darray* arr = malloc(sizeof(struct darray));
  check(arr);
  arr->cells = (Value_Type*) (malloc(sizeof(Value_Type)*size));
  check(arr->cells);
  arr->capacity = size;
  arr->size = 0;
  arr->sorted = false;
  arr->resizes = 0;
  return arr;
} // initialize_set

// function used to tidy the memory from freeing it form memory located when needed
void tidy(struct darray* arr)
{
  if(arr){
    // free memory created by strdup
    for(unsigned i=0; i<arr->size;i++){free(arr->cells[i]); }
    // free array and struct

    free(arr->cells);
    free(arr);
  } // if
} // tidy

// get the size of an array
int size(struct darray* arr){ return arr->size; }

// insert the value into an array
struct darray* insert (Value_Type value, struct darray* arr)
{
  // If we have reached capacity, double size and copy
  if(arr->size >= arr->capacity){
    struct darray* new_arr = initialize_set(arr->capacity*2);
    for(unsigned int i=0;i<arr->size;i++){
      new_arr->cells[i] = arr->cells[i];
    } // for
    // creates a new DArray
    // increment resizes
    // free old darray
    new_arr->size = arr->size;
    new_arr->resizes = arr->resizes+1;
    free(arr->cells);
    free(arr);
    arr = new_arr;
  } // if

  arr->cells[arr->size] = strdup(value);
  arr->size++;

  // changing the array means it may no longer be sorted
  arr->sorted = false;

  return arr;
}
// find takes a value and searches for this element
// depending on the mode it is either binary or linear
bool find (Value_Type value, struct darray* arr)
{
  int size = arr->size;
  //int index = 0;
  if(mode == LINEAR_SEARCH){
    return linearSearch(value, size, arr);
  } // if
  else{ // Binary Search
    if(!arr->sorted){
      if(verbose > 2){
        printf("Dynamic Array not sorted, sorting...\n");
      } // if
      sort(arr,mode);
      if(verbose > 2){
        printf("Dynamic Array sorted\n");
      } // if
      arr->sorted = true;
    } // if
    return binarySearch(value, arr, 0, size-1);
  } // else
  // To supress warning, default return value
  return false;
} // find

// You can make any changes you want to this function
// prints the cells in an array
void print_set (struct darray* arr)
{
  printf("DArray:\n");
  for(unsigned i=0;i<arr->size;i++){
    printf("\t%s\n",arr->cells[i]);
  } // for
} // print_set

// You can make any changes you want to this function
// printing capacity and resizes here
void print_stats (struct darray* arr)
{
  printf("Dynamic array of capacity %d contains %d elements\n",arr->capacity,arr->size);
  printf("Dynamic array was resized %d times\n",arr->resizes);
} // print_stats
