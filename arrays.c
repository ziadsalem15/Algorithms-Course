#include <stdio.h>
#include "arrays.h"
#include "stdlib.h"

/* declare your struct for a person here */
typedef struct person {
  char* name;
  int age;
} person;

static void insert(person **p, char *name, int age, int *nextfreeplace)
{
  person *ptr = (person *)malloc(sizeof(person));

  //static int nextfreeplace = 0;
  /* put name and age into the next free place in the array parameter here */
  p[*nextfreeplace] = ptr;
  p[*nextfreeplace]->name = name;
  p[*nextfreeplace]->age = age;
  /* modify nextfreeplace here */
  (*nextfreeplace)++;
}

int main(int argc, char **argv)
{

  /* declare the people array here */
  person *people[HOW_MANY];
  int nextfreeplace = 0;
  int i;
  for (i = 0; i <= HOW_MANY; i++)
  {
    insert (people, names[i], ages[i], &nextfreeplace);
  }
  int z;
  for (z = 0; z <= HOW_MANY; z++)
  {
    printf("Contents for the people's array: %s %d", people[z]->name, people[z]->age);
  }

  int x;
  for (x = 0; x <= HOW_MANY; x++)
  {
    free(people[x]);
  }
  return 0;
}
