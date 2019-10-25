#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "arrays.h"
/* declare your struct for a person here */
// struct person which consists of character pointer name
//and integer age in years
typedef struct person {
  char* name;
  int age;
} person;

// insert which takes 4 arguments
// array of person pointers
// pointer name
// age in years
// next free place in array
static void insert(person **p, char *name, int age, int *nextfreeplace)
{
  // person pointer to an array which is memory allocation of size person
  person *ptr = malloc(sizeof(person));
  // check that malloc allocated memory for array
  // if not exit
  if (p == NULL)
  {
    exit(EXIT_FAILURE);
  }
  /* put name and age into the next free place in the array parameter here */
  // put name and age in the next free place in the array parameter
  //p[*nextfreeplace]->name = name;
  ptr->name = malloc(sizeof(char) * strlen(name) + 1);
  strcpy(ptr->name, name);
  ptr->age = age;
  p[*nextfreeplace] = ptr;
  /* modify nextfreeplace here */
  // increase next free place by one to point to next position
  (*nextfreeplace)++;

}

int main(int argc, char **argv)
{

  /* declare the people array here */
  // person array of size 7
  person *people[HOW_MANY];
  // next free place in array
  int nextfreeplace = 0;
  // for loop which calls insert and gives it 4 arguments
  // people array, next name, next age and the next free place in array

  for (int i = 0; i < HOW_MANY; i++)
  {
    insert (people, names[i], ages[i], &nextfreeplace);
  }
  // for loop to print the contents of people array, name and age
  for (int z = 0; z < HOW_MANY; z++)
  {
    printf("%d: %s is %d\n",z, people[z]->name, people[z]->age);
  }
  // release the memory allocated by malloc
  for (int x = 0; x < HOW_MANY; x++)
  {
    free(people[x]->name);
    free(people[x]);
  }
  return 0;
}
