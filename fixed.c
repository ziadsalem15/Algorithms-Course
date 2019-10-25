#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// A struct to record pairs of strings
typedef struct pair {
  char* first;
  char* second;
} pair;


// processes a work pair by first storing in
// temp a version of work.first that is all
// lowercase and then storing in work.second
// a version where the first character is
// made uppercase
void process(pair* work)
{
  // pointer used by allocating memory for it
  // of length work.first + 1 * character to have place for every character
  char* temp = (char *)malloc(sizeof(char) * (strlen(work->first) + 1));
  // for loop for iterating over every character in work.first
  int i;
  for(i=0;i<=strlen(work->first);i++){
    // current character is recorded here
    char c = work->first[i];
    // check if upper, save in temp as a small character
    if(isupper(c)){
      temp[i] = tolower(c);
    }
    // else if small or space save character in temp at this position
    else
      temp[i] = c;
  }
  // memory allocation for work.second
  // of length work.first + 1 * character to have place for every character
  work->second = (char *)malloc(sizeof(char) * (strlen(work->first) + 1));
  // copy contents of temp into work->second
  strcpy(work->second,temp);
  // variable used to check if character before was a space or not
  // if yes it is one so change characer at pointer to uppercase else zero.
  // start with one as first characer is h and we wand to change it to H
  int last_space = 1;
  // character pointer pointing to start of work->second
  char* ptr = work->second;
  // while loop to check if pointer is at the end of work->second
  while(*ptr != '\0')
  {
    // if last_space == 1 change to upper
    if(last_space){
      *ptr = toupper(*ptr);
    }
    // else set last_space by checking if last character waa a space
    last_space = *ptr == ((char) ' ');
    // increase pointer by one to point to next character
    ptr++;
  }
  // deallocate memory used by temp using free
  free(temp);
}

// Takes a single string and writes the result to stdout
int main(int argc, char **argv)
{
  // work of type pair to have pair of strings
  pair work;
  // first pair i staken as an argument
  work.first = argv[1];

  // call processes method and provide pointer of work
  // to use it as a pointer in processes
  process(&work);

  // printing string again after edit
  printf("%s becomes %s\n",work.first,work.second);
  // deallocate memory used by work.second using free
  free(work.second);
  return 0;
}
