
#include "sorting.h"

void sort(struct darray* arr, int select){

  switch(select){
    case 2: insertion_sort(arr); break;
    case 3: quick_sort(arr); break;
    case 4:
    case 5:
    case 6:  // Add your own choices here
    defualt: 
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


void insertion_sort(struct darray* arr){
 fprint(stderr, "Not implemented\n");
 exit(-1);
}


// Hint: you probably want to define a helper function for the recursive call
void quick_sort(struct darray* arr) {
 fprint(stderr, "Not implemented\n");
 exit(-1);
}
