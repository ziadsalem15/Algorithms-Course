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

static person* insert_start(person *p, char *name, int age)
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
static person* insert_end(person *p, char *name, int age)
{
  person *new_person_end = malloc(sizeof(person));
  // check that malloc allocated memory for array
  // if not exit
  if (new_person_end == NULL)
  {
    exit(1);
  }
  new_person_end->name = name;
  new_person_end->age = age;

  person* new_list = malloc(sizeof(person));
  new_list->name = name;
  new_list->age = age;
  new_list->next = NULL;

  if (p == NULL)
  {
    p = new_list;
  }
  else
  {
    person* end = p;
    while (end->next != NULL)
    {
      end = end->next;
    }

    end->next = new_list;

  }
  return p;

}

int main(int argc, char **argv)
{

  /* declare the people array here */
  // person array of size 7
  person *people = NULL;
  if (argc == 1)
  {
    for (int i = 0; i < HOW_MANY; i++)
    {
      people = insert_start(people, names[i], ages[i]);
    }
  }
  else if(argc == 2)
  {
    if (0 == strcmp(argv[1], "insert_start"))
    {
      for (int i = 0; i < HOW_MANY; i++)
      {
        people = insert_start(people, names[i], ages[i]);
      }
    }
    else if (0 == strcmp(argv[1], "insert_end"))
    {
      for (int i = 0; i < HOW_MANY; i++)
      {
        people = insert_end(people, names[i], ages[i]);
      }
    }
    else
    {
      fprintf(stderr, "%s\n" , "Wrong Command Line Arguments Used");
      return 5;
    }
  }
  else
  {
    fprintf(stderr, "%s\n" , "Wrong Command Line Arguments Used");
    return 5;
  }

  while (people != NULL)
  {
    printf("Name: %s, age: %d\n", people->name, people->age);
    free(people);
    people = people->next;
  }


  return 0;
}
