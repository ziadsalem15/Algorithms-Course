#include <stdlib.h>
#include <stdio.h>
#include "sorting.h"

void sort(struct darray* arr, int select){
  int size = arr->size;
  switch(select){
    case BINARY_SEARCH_ONE   : insertion_sort(arr); break;
    case BINARY_SEARCH_TWO   : quick_sort(arr, 0, size-1); break;
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
  print_set(array);
}

int partition(struct darray* arr, int startIndex, int lastIndex)
{
  Value_Type pivot = arr->cells[lastIndex];
  int indexSmallest = (startIndex - 1);
  for (int i = startIndex; i <= lastIndex - 1; i++)
  {
    if (arr->cells[i] < pivot)
    {
      indexSmallest++;
      swap(&arr->cells[indexSmallest], &arr->cells[i]);
    }
  }
  swap(&arr->cells[indexSmallest + 1], &arr->cells[lastIndex]);
  return (indexSmallest + 1);
}

// Hint: you probably want to define a helper function for the recursive call
void quick_sort(struct darray* arr, int startIndex, int lastIndex) {
 if (startIndex < lastIndex)
 {
   int partitionIndex = partition(arr, startIndex, lastIndex);
   quick_sort(arr, startIndex, partitionIndex - 1);
   quick_sort(arr, partitionIndex + 1, lastIndex);
 }
}
