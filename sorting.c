#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sorting.h"

void sort(struct darray* arr, int select){
  switch(select){
    case BINARY_SEARCH_ONE   : insertion_sort(arr); break;
    case BINARY_SEARCH_TWO   : quick_sort(arr); break;
    case BINARY_SEARCH_THREE : merge_sort(arr); break;
    case BINARY_SEARCH_FOUR  : //bucket_sort(arr); break;
    case BINARY_SEARCH_FIVE  : //bubble_sort(arr); break; // Add your own choices here
    default:
      fprintf(stderr,
              "The value %d is not supported in sorting.c\n",
              select);
      // Keep this exit code as the tests treat 23 specially
      exit(23);
  }
}


// You may find this helpful
void swap(char* *a, char* *b)
{
        char* temp = *a;
        *a = *b;
        *b = temp;
}


void insertion_sort(struct darray* array)
{
  for (int i = 1; i < array->size; i++)
  {
    int z = i;
    while (z > 0 && compare(array->cells[z-1] , array->cells[z]) > 0)
    {
      swap(&array->cells[z - 1], &array->cells[z]);
      z--;
    }
  }
}



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
     }
     else{
       less_than = insert(arr->cells[i], less_than);
     }
   }
   quick_sort(less_than);
   quick_sort(greater_than);
   for(int j = 0; j < less_than->size; j++)
   {
     swap(&arr->cells[j], &less_than->cells[j]);
   }
   swap(&arr->cells[less_than->size], &arr->cells[pivot]);
   int initial = less_than->size + 1;
   for(int z = 0; z < greater_than->size; z++)
   {
     swap(&arr->cells[z + initial], &greater_than->cells[z]);
   }
   tidy(greater_than);
   tidy(less_than);
 }
}
void merge_sort(struct darray* array)
{
  if (array->size > 1)
  {
    int mid = array->size / 2;
    struct darray* left = initialize_set(mid);
    //left->cells = (char**)malloc(mid * sizeof(char*));
    //left->size = 0;
    //struct darray* left = initialize_set(mid);
    //struct darray* right = initialize_set(mid);
    for (int i = 0; i < mid; i++)
    {
      left->cells[i] = array->cells[i];
      left->size++;
    }
    struct darray* right = initialize_set((array->size) - mid);
    //right->cells = (char**)malloc((array->size - mid) * sizeof(char*));
    //right->size = 0;
    for (int i = 0; i < ((array->size) - mid); i++)
    {
      right->cells[i] = array->cells[i+mid];
      right->size++;
    }
    merge_sort(left);
    merge_sort(right);
    int x = 0;
    int y = 0;
    int z = 0;
    while (x < left->size && y < right->size)
    {
      if (compare(left->cells[x], right->cells[y]) < 0)
      {
        array->cells[z] = left->cells[x];
        x++;
      }
      else
      {
        array->cells[z] = right->cells[y];
        y++;
      }
      z++;
    }
    while (x < left->size)
    {
      array->cells[z] = left->cells[x];
      x++;
      z++;
    }
    while (y < right->size)
    {
      array->cells[z] = right->cells[y];
      y++;
      z++;
    }
    free(left->cells);
    free(right->cells);
    free(left);
    free(right);
    //tidy(left);
    //tidy(right);
  }
}
