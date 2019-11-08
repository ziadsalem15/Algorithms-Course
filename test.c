#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "slists.h"
//#include "slists.c"
#include "data.h"


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
