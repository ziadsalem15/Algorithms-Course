#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sorting.h"

void sort(struct darray* arr, int select){
  switch(select){
    case BINARY_SEARCH_ONE   : insertion_sort(arr); break;
    case BINARY_SEARCH_TWO   : quick_sort(arr); break;
    case BINARY_SEARCH_THREE : merge_sort(arr); break;
    case BINARY_SEARCH_FOUR  : bucket_sort(arr); break;
    case BINARY_SEARCH_FIVE  : bubble_sort(arr); break; // Add your own choices here
    default:
      fprintf(stderr,
              "The value %d is not supported in sorting.c\n",
              select);
      // Keep this exit code as the tests treat 23 specially
      exit(23);
  }
} // sort

// swap used in some methods to sawap some characters
// You may find this helpful
void swap(char* *a, char* *b)
{
        char* temp = *a;
        *a = *b;
        *b = temp;
} // swap

// inserton sort implemented which you compare if element before bigger than
// then swap with element afer it.
void insertion_sort(struct darray* array)
{
  for (int i = 1; i < array->size; i++)
  {
    int z = i;
    while (z > 0 && compare(array->cells[z-1] , array->cells[z]) > 0)
    {
      swap(&array->cells[z - 1], &array->cells[z]);
      z--;
    } // while
  } // for
} // insertion_sort


// quick sort algorithm implemented here where we first check if array size is
// bigger than one then set the pvot where her it points to the last element
// if greater_than then call insert and give it greater_than
// if smaller than do the opposite
// make a recursive call by applying quick sort on less than pivot and greater t
// than pivot
// Hint: you probably want to define a helper function for the recursive call
void quick_sort(struct darray* arr) {
 if (arr->size > 1)
 {
   struct darray* greater_than = initialize_set(1);
   struct darray* less_than = initialize_set(1);
   int pivot = arr->size - 1;
   for (int i = 0; i < arr->size - 1; i++)
   {
     if (compare(arr->cells[i], arr->cells[pivot]) >= 0)
     {
       greater_than = insert(arr->cells[i], greater_than);
     } // if
     else{
       less_than = insert(arr->cells[i], less_than);
     } // else
   } // for
   quick_sort(less_than);
   quick_sort(greater_than);
   // for loop to swap current element in darray with less than darray
   for(int j = 0; j < less_than->size; j++)
   {
     swap(&arr->cells[j], &less_than->cells[j]);
   } // for
   swap(&arr->cells[less_than->size], &arr->cells[pivot]);
   int initial = less_than->size + 1;
   for(int z = 0; z < greater_than->size; z++)
   {
     swap(&arr->cells[z + initial], &greater_than->cells[z]);
   } // for
   // tidy memory here
   tidy(greater_than);
   tidy(less_than);
 } // if
} // quick_sort
// merge sort implemented here where you check uf array size is bigger than one
// then set mid at the middle of the array
// initialize left and right by giving them their sizes
void merge_sort(struct darray* array)
{
  if (array->size > 1)
  {
    int mid = array->size / 2;
    struct darray* left = initialize_set(mid);
    struct darray* right = initialize_set((array->size) - mid);
    // add values to left by setting to it to array but till mid only
    // right is opposite
    for (int i = 0; i < mid; i++)
    {
      left->cells[i] = array->cells[i];
      left->size++;
    } // for
    for (int i = 0; i < ((array->size) - mid); i++)
    {
      right->cells[i] = array->cells[i+mid];
      right->size++;
    } // for
    // merge left and right recursively
    merge_sort(left);
    merge_sort(right);
    // setting x, y, z to zero to use in while loop
    int x = 0;
    int y = 0;
    int z = 0;
    while (x < left->size && y < right->size)
    {
      if (compare(left->cells[x], right->cells[y]) < 0)
      {
        array->cells[z] = left->cells[x];
        x++;
      } // if
      else
      {
        array->cells[z] = right->cells[y];
        y++;
      } // else
      z++;
    }
    while (x < left->size)
    {
      array->cells[z] = left->cells[x];
      x++;
      z++;
    } // while
    while (y < right->size)
    {
      array->cells[z] = right->cells[y];
      y++;
      z++;
    } // while
    // free memory allocation used to avoid having eeeors
    free(left->cells);
    free(right->cells);
    free(left);
    free(right);
  } // if
} // merge_sort

// bubble sort implemented here
void bubble_sort(struct darray* array)
{
  // loop to go over teh array size and array size - i
  // ompare if current place is bugher than th next
  // then swap
  for (int i = 0; i < ((array->size) - 1); i++)
  {
    for (int j = 0; j < ((array->size) - i - 1); j++)
    {
      if (compare(array->cells[j], array->cells[j+1]) > 0)
      {
        swap(&(array->cells[j]), &(array->cells[j+1]));
      } // if
    } // for
  } // for
} // bubble_sort
// bucket sort implemented here where array is taken and checks if size > 1
void bucket_sort(struct darray* array)
{
  if (array->size > 1)
  {
    // creating a buckets array which is an array of dynamic arrays
    struct darray *buckets[150];
    // set each bucket to null
    for (int i = 0; i < 150; i++)
    {
      buckets[i] = NULL;
    } // for
    // if buckets key is present insert this cell into buckets
    // otherwise initialize an dthen insert
    for (int i = 0; i < array->size; i++)
    {
      int key = ((int) array->cells[i][0]);
      if (buckets[key] != NULL)
      {
        buckets[key] = insert(array->cells[i], buckets[key]);
      }  // if
      else
      {
        buckets[key] = initialize_set(1);
        buckets[key] = insert(array->cells[i], buckets[key]);
      } // else
    } // for
    // set index to 0
    int index = 0;
    // if buckets is  present sort using
    // insertion sort and then swap.
    for (int i = 0; i < 150; i++)
    {
      if (buckets[i] != NULL){
        insertion_sort(buckets[i]);
        for (int j = 0; j < (buckets[i]->size); j++)
        {
          swap(&array->cells[index], &buckets[i]->cells[j]);
          index++;
        } // for
      } // if
    } // for
    for (int i = 0; i < 150; i++)
    {
      // tidy memory at the end
      tidy(buckets[i]);
    } // fro
  }  //if
}// bucket_sort
