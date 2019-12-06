#include <stdlib.h>
#include <stdio.h>
#include "sorting.h"

void sort(struct darray* arr, int select){
  switch(select){
    case BINARY_SEARCH_ONE   : insertion_sort(arr); break;
    case BINARY_SEARCH_TWO   : quick_sort(arr); break;
    case BINARY_SEARCH_THREE :
    case BINARY_SEARCH_FOUR  :
    case BINARY_SEARCH_FIVE  :  // Add your own choices here
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
   struct darray* less_than = initialize_set(1);
   struct darray* greater_than = initialize_set(1);
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
     swap(&arr->cells[z + initial], &less_than->cells[z]);
   }
   tidy(less_than);
   tidy(greater_than);
 }
}
