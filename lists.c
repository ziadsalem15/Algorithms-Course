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
  new_person_end->next = NULL;

  if (p == NULL)
  {
    return new_person_end;
  }
  else
  {
    person* end = p;
    while (end->next != NULL)
    {
      end = end->next;
    }

    end->next = new_person_end;
    return p;
  }

}
static person* insert_sorted(person *p, char *name, int age, int (*compare_people)(person*, person*))
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
  new_person_end->next = NULL;

  if(p == NULL ||compare_people(p, new_person_end) > 0)
  {
    free(new_person_end);
    return insert_start(p, name, age);
  }
  else
  {
    person* end = p;
    person* previous = NULL;
    while(end != NULL && compare_people(new_person_end, end) >= 0)
    {
      previous = end;
      end = end->next;
    }
    if (end == NULL)
    {
      previous->next = new_person_end;
    }
    else
    {
      previous->next = new_person_end;
      new_person_end->next = end;
    }
    return p;
  }

}
int compare_people_by_name(person* person1, person* person2)
{
  if (person1 == NULL || person2 == NULL)
    exit(2);
  return strcmp(person1->name, person2->name);
}
int compare_people_by_age(person* person1, person* person2)
{
  if (person1 == NULL || person2 == NULL)
    exit(2);
  return (person1->age - person2->age);
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
  else if((argc == 2) || ((argc > 2) && 0 == strcmp(argv[1], "insert_sorted")))
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
    else if (0 == strcmp(argv[1], "insert_sorted"))
    {
      int (*compare_people)(person*, person*);
      if (argc == 2)
      {
        compare_people = &compare_people_by_name;
      }
      else if (argc > 3)
      {
        fprintf(stderr, "%s\n" , "Wrong Command Line Arguments Used");
        exit(2);
      }
      else if (0 == strcmp(argv[2], "name"))
      {
        compare_people = &compare_people_by_name;
      } // if
      else if (0 == strcmp(argv[2], "age"))
      {
        compare_people = &compare_people_by_age;
      }
      else if (0 != strcmp(argv[2], "age") || 0 != strcmp(argv[2], "name"))
      {
        fprintf(stderr, "%s\n" , "Wrong Command Line Arguments Used");
        exit(2);
      }

      for (int i = 0; i < HOW_MANY; i++)
      {
        people = insert_sorted(people, names[i], ages[i], compare_people);
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

  person* temp = people;
  while (temp != NULL)
  {
    printf("Name: %s, age: %d\n", temp->name, temp->age);
    temp = temp->next;
  }

  while (people != NULL){
    temp = people;
    people = people->next;
    free(temp);
  }


  return 0;
}
