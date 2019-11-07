#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "data.h"
/* declare your struct for a person here */
// struct person which consists of character pointer name
//and integer age in years
typedef struct person {
  char* name;
  int age;
  struct person *next;
} person;

static person* insert(person *p, char *name, int age)
{
  person *new_person = malloc(sizeof(person));
  // check that malloc allocated memory for array
  // if not exit
  if (new_person == NULL)
  {
    exit(1);
  }

  new_person->name = name;
  new_person->age = age;
  new_person->next = p;
  return new_person;
}

int main(int argc, char **argv)
{

  /* declare the people array here */
  // person array of size 7
  person *people = NULL;

  // for loop which calls insert and gives it 4 arguments
  // people array, next name, next age and the next free place in array
  int i;
  for (i = 0; i < HOW_MANY; i++)
  {
    people = insert (people, names[i], ages[i]);
  }
  
  while (people != NULL)
  {
    printf("%s is %d\n", people->name, people->age);
    people = people->next;
    
  }
  free(people);

  return 0;
}
