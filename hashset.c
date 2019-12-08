#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>
#include <math.h>

#include "global.h"
#include "hashset.h"

// Can be redefined if Value_Type changes
int compare(Value_Type a, Value_Type b){
  return strcmp(a,b);
}

// Helper functions for finding prime numbers
bool isPrime (int n)
{
  for (int i = 2; i*i <= n; i++)
    if (n % i == 0)
      return false;
  return true;
}

int nextPrime(int n)
{
  for (; !isPrime(n); n++);
  return n;
}

// Your code

struct hashset* initialize_set (int size)
{
  struct hashset* set = malloc(sizeof(struct hashset));
  set->cells = (cell*)malloc(sizeof(cell)*size);
  set->size = size;
  set->num_entries = 0;
  set->collisionsValue = 0;
  for (int i = 0; i < size; i++)
  {
    cell* newCell = malloc(sizeof(cell));
    newCell->element = NULL;
    newCell->state = empty;
    set->cells[i] = *newCell;
    free(newCell);
  }
  return set;
}

void tidy(struct hashset* set)
{
  for(int i = 0; i<set->size; i++)
  {
    if (set->cells[i].state == in_use)
    {
      free(set->cells[i].element);
    }
  }
  free(set->cells);
  free(set);

}

int size(struct hashset* set)
{
  return set->num_entries;
}

struct hashset* insert (Value_Type value, struct hashset* set)
{
  // TODO code for inserting into hash table
  if (find(value, set))
  {
    return set;
  }
  if (mode == HASH_1_LINEAR_PROBING || mode == HASH_2_LINEAR_PROBING)
  {
    if(set->size == set->num_entries)
    {
      set = resize(set);
    }
    for(int i = 0; i <= set->size; i++)
    {
      int hashKey = getHashKey(value, set, i);
      if (set->cells[hashKey].state == empty)
      {
        set->cells[hashKey].element = strdup(value);
        set->cells[hashKey].state = in_use;
        set->num_entries += 1;
        break;
      }
      set->collisionsValue++;
    }
    return set;
  }
}
struct hashset* resize(struct hashset* setToResize)
{
  struct hashset* resizedSet = initialize_set(setToResize->size * 2);
  for(int i = 0; i < setToResize->size; i++)
  {
    resizedSet = insert(setToResize->cells[i].element, resizedSet);
  }
  tidy(setToResize);
  return resizedSet;
}

int getHashKey(Value_Type value, struct hashset* set, int i)
{
  return ((int)value + i) % set->size;
}

bool find (Value_Type value, struct hashset* set)
{
  for (int i = 0; i < set->size; i++)
  {
    int hashKey = getHashKey(value, set, i);
    if (set->cells[hashKey].state != empty && compare(set->cells[hashKey].element, value) == 0)
    {
      return true;
    }
  }
  return false;
}

void print_set (struct hashset* set)
{
  // TODO code for printing hash table
  for (int i = 0; i < set->size; i++)
  {
    if(set->cells[i].state == in_use)
    {
      printf("Element in each cell is : %s\n", (set->cells[i].element));
    }
  }
}

void print_stats (struct hashset* set)
{
  // TODO code for printing statistics
  printf("Number of collisions is: ");
  printf("%d\n", set->collisionsValue);
}
