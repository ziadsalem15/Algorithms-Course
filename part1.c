#include <stdio.h>
#include <stdbool.h>

// main method
int main(int argc, char **argv)
{
  // current character
  int character = 0;
  // from capital to small letter
  int upperToLow = 0;
  // from small to capital letter
  int lowerToUP = 0;
  // total number of characters so far
  int totalCharacters = 0;
  // input and output file
  FILE *inputFile;
  FILE *outputFile;

  // array for files
  char chosenInputFile[50];
  char chosenOutputFile[50];

  // scanf to read name of files from input
  scanf("%s", chosenInputFile);
  scanf("%s", chosenOutputFile);

  // open input and output file
  inputFile = fopen(chosenInputFile, "r");
  outputFile = fopen(chosenOutputFile, "w");

  // check is input i sthere and can be opened
  if (inputFile == NULL)
  {
    printf("Input file cannot be opened !!\n");
  } // if 

  // while loop to go through the full nukber of characters
  while ((character = getc(inputFile)) != EOF)
  {
    // increase no of characters
    totalCharacters ++;
    // if condiition to check if lower
    if (islower(character))
    {
      // change case and put in output file & inc no of changed
      putc(toupper(character), outputFile);
      lowerToUP++;
    } // if
    else if (isupper(character))
    {
      // change case and put in output file and increase no of changed
      putc(tolower(character), outputFile);
      upperToLow++;
    } // else if

    else
    {
      putc(character, outputFile);
    } // else
  } // while
  // print summary
  printf("Read %d characters in total, %d converted to upper-case, %d to lower-case\n", totalCharacters, upperToLow, lowerToUP);
  // close input and output file
  fclose(inputFile);
  fclose(outputFile);
} // main
