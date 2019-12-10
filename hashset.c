#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>
//#include <math.h>

#include "global.h"
#include "hashset.h"

// Can be redefined if Value_Type changes
int compare(Value_Type a, Value_Type b){
  return strcmp(a,b);
} // compare
// math.h wasn't working on COMP Judge so i did that instead.
double power(int base, unsigned int p)
{
  if (p == 0)
    return 1;
  else if (p % 2 == 0)
    return power(base, p/2) * power(base, p/2);
  else
    return base * power(base, p/2) * power(base, p/2);
} // pow

// Helper functions for finding prime numbers
// method to check if number is prime or not
bool isPrime (int n)
{
  for (int i = 2; i*i <= n; i++)
    if (n % i == 0)
      return false;
  return true;
} // isPrime

// method to get the next prime number
int nextPrime(int n)
{
  for (; !isPrime(n); n++);
  return n;
} // nextPrime

// Your code
// function to allocate memory with the size given for the set to create
//  it sets element to null and state as empty
// other things to zero
// return the set we initialized.
struct hashset* initialize_set (int size)
{
  struct hashset* set = (struct hashset*)malloc(sizeof(struct hashset));
  check(set);
  if(!isPrime(size))
  {
    size = nextPrime(size);
  } // if
  set->cells = (cell*)malloc(sizeof(cell)*size);
  check(set->cells);
  set->size = size;
  set->num_entries = 0;
  set->collisionsValue = 0;
  for (int i = 0; i < set->size; i++)
  {
    set->cells[i].element = NULL;
    set->cells[i].state = empty;
  } // for
  return set;
} // initialize_set

// tidy to clean up memory after finishing working
// it takes the set we want to free and free every thing inside it
void tidy(struct hashset* set)
{
  if (set)
  {
    for(int i = 0; i < set->size; i++)
    {
      if (set->cells[i].state == in_use)
      {
        free(set->cells[i].element);
      } // if
    } // for
    free(set->cells);
    free(set);
  } // if
} // tidy

// returns size of set depending on number of elements in the set.
int size(struct hashset* set)
{
  return set->num_entries;
} // size

// get hash key by getting using sum if mode less than 2
int getHashKey(char* value)
{
  if (mode < 3)
    return getHashKeybySum(value);
  // otherwise use hash key using poly
  else if ((mode < 7) && (mode != 3))
    return hashInPoly(value);
  else
    exit(-1);
} // getHashKey
// get hash key using sum
int getHashKeybySum(char* value)
{
  // initialize sum to 0 and then loop over the length of string and sum
  int sum = 0;
  for(int i = 0; i < strlen(value); i++)
  {
    sum = sum + (int)value[i];
  } // for
  return sum;
} // getHashKeybySum

// get hash key using poly
int hashInPoly(char* value)
{
  // initialize sum to 0 and then loop over the length of string and sum
  int sum = 0;
  for(int i = 0; i < strlen(value); i++)
  {
    sum = sum + (int)value[i] * power(10, strlen(value) - 1 - i);
  } // for
  return sum;
} // hashInPoly

//// get hash key using poly
int hashInPoly2nd(char* value)
{
  // initialize sum to 0 and then loop over the length of string and sum
  int sum = 0;
  for(int i = 0; i < strlen(value); i++)
  {
    sum = sum + (int)value[i] * power(20, strlen(value) - 1 - i);
  } // for
  return sum;
} // hashInPoly2nd

// if the set is full resize it by making a new set by multiplying size by 2
// then insert the old elements in the new set resized
// tidy the old set at the end
struct hashset* resize(struct hashset* setToResize)
{
  struct hashset* resizedSet = initialize_set(setToResize->size * 2);
  for(int i = 0; i < setToResize->size; i++)
  {
    resizedSet = insert(setToResize->cells[i].element, resizedSet);
  } // for
  tidy(setToResize);
  return resizedSet;
} // resize

// function used to compress, it takes value, size, index
int compressFunction(Value_Type value, int size, int i)
{
  // checks each mode and depending on it hashes by a different way
  if ((mode == HASH_1_LINEAR_PROBING) || (mode == HASH_2_LINEAR_PROBING))
    return (getHashKey(value) + i) % size;
  else if ((mode == HASH_1_QUADRATIC_PROBING) || (mode == HASH_2_QUADRATIC_PROBING))
    return (getHashKey(value) + (int)power(i, 2)) % size;
  else if (mode == HASH_1_DOUBLE_HASHING)
    return (hashInPoly(value) + i * hashInPoly2nd(value)) % size;
  else if (mode == HASH_2_DOUBLE_HASHING)
    return (hashInPoly2nd(value) + i * hashInPoly(value)) % size;
  // exit if not any of the modes
  else
    exit(1);

} // compressFunction


// insert function which takes the value we want to insert and the set
struct hashset* insert (Value_Type value, struct hashset* set)
{
  // TODO code for inserting into hash table
  // if the value is already in the set don't insert it as we don't want any dublicates
  if (find(value, set))
  {
    return set;
  } // if
  // if it is not the mode we want don't go inside
  // if size is not enough multiply by 2
  if(set->size == set->num_entries)
  {
    set = resize(set);
  }
  // // get hashkey and then insert elemnt in a free cell
  for(int i = 0; i < set->size; i++)
  {
    int hashKey = compressFunction(value, set->size, i);
    if (set->cells[hashKey].state == empty)
    {
      set->cells[hashKey].element = strdup(value);
      set->cells[hashKey].state = in_use;
      set->num_entries += 1;
      return set;
    } // if
    else
      // increse no of collisions
      set->collisionsValue++;
  } // else
  return set;
} // insert
// function to check is the element is inside the set or not
bool find (Value_Type value, struct hashset* set)
{
  for (int i = 0; i < set->size; i++)
  {
    // calling compress to get the hash key depending on the node
    int hashKey = compressFunction(value, set->size, i);
    if (set->cells[hashKey].state != empty && compare(set->cells[hashKey].element, value) == 0)
    {
      return true;
    } // if
  } // for
  return false;
} // find

// printing element in each cell after checking if it is in use or not
void print_set (struct hashset* set)
{
  // TODO code for printing hash table
  for (int i = 0; i < set->size; i++)
  {
    if(set->cells[i].state == in_use)
    {
      printf("Element in each cell is : %s\n", (set->cells[i].element));
    } // if
  } // for
} // print_set

// printing number of collisions at the end
void print_stats (struct hashset* set)
{
  // TODO code for printing statistics
  printf("Number of collisions is: ");
  printf("%d\n", set->collisionsValue);
} // print_stats
