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
void process(pair *work)
{
  char* temp = (char *)malloc(sizeof(char) * (strlen(work->first) + 1));
  for(int i=0;i<=strlen(work->first);i++){
    char c = work->first[i];
    if(isupper(c)){
      temp[i] = tolower(c);
    }
    else
      temp[i] = c;
  }
  work->second = (char *)malloc(sizeof(char) * (strlen(work->first) + 1));
  strcpy(work->second,temp);
  int last_space = 1;
  char* ptr = work->second;
  while(*ptr){
    if(last_space){
      *ptr = toupper(*ptr);
    }
    last_space = *ptr == ((char) ' ');
    ptr++;
  }
}

// Takes a single string and writes the result to stdout
int main(int argc, char **argv)
{
  pair work;
  work.first = argv[1];

  process(&work);

  printf("%s becomes %s\n",work.first,work.second);
}
