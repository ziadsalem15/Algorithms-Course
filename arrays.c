#include <stdio.h>
#include "arrays.h"

/* declare your struct for a person here */

static void insert(/* array parameter */, char *name, int age) 
{
  static int nextfreeplace = 0;
  /* put name and age into the next free place in the array parameter here */
  /* modify nextfreeplace here */
}

int main(int argc, char **argv) 
{

  /* declare the people array here */

  for (... < HOW_MANY ...) 
  {
    insert (people, names[...], ages[...]);
  }

  /* print the people array here*/

  return 0;
}
