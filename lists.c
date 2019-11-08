#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "data.h"
/* declare your struct for a person here */
// struct person which consists of character pointer name
//and integer age in years
// and next used topoint tonext element in linke dlist
typedef struct person {
  char* name;
  int age;
  struct person *next;
} person;

// insert_start method which put a nw perosn in the req location
static person* insert_start(person *p, char *name, int age)
{
  // new person pointer used to point to firt element
  person *new_person = malloc(sizeof(person));
  // check that malloc allocated memory for pointer
  // if not exit
  if (new_person == NULL)
  {
    exit(1);
  } // if

  // set the data for new person
  new_person->name = name;
  new_person->age = age;

  // set the new person next to point to the current list
  new_person->next = p;

  // return the new list which is a pointer to the new person
  return new_person;
} // insert start

// insert new person at end of list
static person* insert_end(person *p, char *name, int age)
{
  // create new space for nw person
  person *new_person_end = malloc(sizeof(person));

  // check that malloc allocated memory for array
  // if not exit
  if (new_person_end == NULL)
  {
    exit(1);
  } // if

  // set the data for the new person
  new_person_end->name = name;
  new_person_end->age = age;
  new_person_end->next = NULL;

  // if current list is empty do as part 1
  if (p == NULL)
  {
    return new_person_end;
  } // if
  else
  {
    // end used to reach end element
    person* end = p;
    // iterate until you reach end of list
    while (end->next != NULL)
    {
      end = end->next;
    } // while

    // add element at the end
    end->next = new_person_end;

    return p;
  } // else
} // insert_end

// insert_sorted method ued to put new person in ascending order according
// to either name or age
static person* insert_sorted(person *p, char *name, int age, int (*compare_people)(person*, person*))
{
  // create new space for new person
  person *new_person_end = malloc(sizeof(person));

  // check that malloc allocated memory for array
  // if not exit
  if (new_person_end == NULL)
  {
    exit(1);
  } // if

  // set data for new person
  new_person_end->name = name;
  new_person_end->age = age;
  new_person_end->next = NULL;

  // check if null or new person less than 1st item
  if(p == NULL ||compare_people(p, new_person_end) > 0)
  {
    // free it and do the same as insert_start
    free(new_person_end);
    return insert_start(p, name, age);
  } // if
  else
  {
    // set two pointers one at the current selection
    // the other for the previous one to put in between
    person* end = p;
    person* previous = NULL;
    // while not at the end and finding the last item that is smaller than the new person
    while(end != NULL && compare_people(new_person_end, end) >= 0)
    {
      // set pevious as current
      previous = end;
      // make current the next element
      end = end->next;
    } // while

    // if this is the biggest element we want to add
    if (end == NULL)
    {
      // move previous
      previous->next = new_person_end;
    } // if
    else
    {
      // add between current and previous
      previous->next = new_person_end;
      new_person_end->next = end;
    } // else 

    return p;
  }

}
// comapre people according to their names alphabatically
int compare_people_by_name(person* person1, person* person2)
{
  // check if any of them is null
  if (person1 == NULL || person2 == NULL)
    exit(2);
  // compare both names
  return strcmp(person1->name, person2->name);
} // compare_people_by_name

// compare people according to their age s
int compare_people_by_age(person* person1, person* person2)
{
  // check is any is null
  if (person1 == NULL || person2 == NULL)
    exit(2);

  // compare both ages
  return (person1->age - person2->age);
}// compare_people_by_age


int main(int argc, char **argv)
{

  /* declare the people array here */
  // person linked list set to NUll
  person *people = NULL;
  // check if only 1 argument call insert start
  if (argc == 1)
  {
    for (int i = 0; i < HOW_MANY; i++)
    {
      people = insert_start(people, names[i], ages[i]);
    } // for
  } // if

  // check if two arguments or more than 2 and it is insert sorted
  else if((argc == 2) || ((argc > 2) && 0 == strcmp(argv[1], "insert_sorted")))
  {
    // if 1st argument is insert start
    // call method
    if (0 == strcmp(argv[1], "insert_start"))
    {
      for (int i = 0; i < HOW_MANY; i++)
      {
        people = insert_start(people, names[i], ages[i]);
      } // for
    } // if

    // if 1st argument is insert end
    // call method
    else if (0 == strcmp(argv[1], "insert_end"))
    {
      for (int i = 0; i < HOW_MANY; i++)
      {
        people = insert_end(people, names[i], ages[i]);
      } // for
    } // else if

    // if 1st argument is insert sorted
    else if (0 == strcmp(argv[1], "insert_sorted"))
    {
      // declaring a pointer to be used for comparing method
      int (*compare_people)(person*, person*);

      // if not specified name or age
      // set as name
      if (argc == 2)
      {
        compare_people = &compare_people_by_name;
      } // if

      // if argc more than 3 something is wrong and exit
      else if (argc > 3)
      {
        fprintf(stderr, "%s\n" , "Wrong Command Line Arguments Used");
        exit(2);
      } // else if

      // if 2nd arg is name set as name
      else if (0 == strcmp(argv[2], "name"))
      {
        compare_people = &compare_people_by_name;
      } // else if

      // if 2nd arg is age set as age
      else if (0 == strcmp(argv[2], "age"))
      {
        compare_people = &compare_people_by_age;
      } // else if

      // if 2nd arg is not name or age output a message an dexit
      else if (0 != strcmp(argv[2], "age") || 0 != strcmp(argv[2], "name"))
      {
        fprintf(stderr, "%s\n" , "Wrong Command Line Arguments Used");
        exit(2);
      } // else if

      // call method
      for (int i = 0; i < HOW_MANY; i++)
      {
        people = insert_sorted(people, names[i], ages[i], compare_people);
      } // for
    } // else if

    // else if sth wrong happened output a message and exit
    else
    {
      fprintf(stderr, "%s\n" , "Wrong Command Line Arguments Used");
      return 5;
    } // else
  } // else if

  // else if sth wrong happened output a message and exit
  else
  {
    fprintf(stderr, "%s\n" , "Wrong Command Line Arguments Used");
    return 5;
  } // else

  // set a temporary pointer for printing
  person* temp = people;
  // check while if not null
  // print name and age
  // set pointer to next element
  while (temp != NULL)
  {
    printf("Name: %s, age: %d\n", temp->name, temp->age);
    temp = temp->next;
  } // while

  // check while if not null
  // set temp to people
  // free temp after porinting to each lement usingnext
  while (people != NULL){
    temp = people;
    people = people->next;
    free(temp);
  } // while

  return 0;
} // main
