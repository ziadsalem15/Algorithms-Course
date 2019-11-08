#include <stdio.h>
#include <stdlib.h>
#include "slists.h"

// insert_start method which put a nw perosn in the req location
person* insert_start(person *p, char *name, int age)
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
person* insert_end(person *p, char *name, int age)
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
person* insert_sorted(person *p, char *name, int age, int (*compare_people)(person*, person*))
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
