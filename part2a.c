#include <stdio.h>
#include <string.h>

// main method
int main (int argc, char *argv[])
{
  // longest Arg
  int longestArg;
  // no of arguments
  int argumentCount;
  if (argc > 1)
  {
    // start with 1
    longestArg = 1;
    argumentCount = 1;

    // while loop to iterate over argc
    while (argumentCount < argc)
    {
      // strlen used to check if current argument is longer than longest argument
      if (strlen(argv[argumentCount]) > strlen(argv[longestArg]))
      {
        longestArg = argumentCount;
      }
      // inc by 1
      argumentCount++;
    }
    // print longest argument
    printf("%s\n", argv[longestArg]);
    return 0;
  }
  // print error
  printf("Error: expected some command-line parameters\n");
  return 0;
}
