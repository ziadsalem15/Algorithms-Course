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

struct person insert(person **p, char *name, int age)
{
  struct person *new_person = malloc(sizeof(person));
  // check that malloc allocated memory for array
  // if not exit
  if (new_person == NULL)
  {
    exit(1);
  }

  new_person->name = malloc(sizeof(char) * strlen(name) + 1);
  // copy contents of name into ptr->name
  strcpy(new_person->name, name);
  // put age in the next free place
  new_person->next = (*p);
  //p[*nextfreeplace] = ptr;
  // increase next free place by one to point to next position
  //(*nextfreeplace)++;
  return *new_person;
}

int main(int argc, char **argv)
{

  /* declare the people array here */
  // person array of size 7
  struct person *people = NULL;
  // next free place in array
  //int nextfreeplace = 0;
  // for loop which calls insert and gives it 4 arguments
  // people array, next name, next age and the next free place in array
  /*int i;
  for (i = 0; i < HOW_MANY; i++)
  {
    insert (people, names[i], ages[i]);
    //insert (people, names[i], ages[i], &nextfreeplace);
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
  }*/
  return 0;
}
