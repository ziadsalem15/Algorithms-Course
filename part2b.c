#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// method from c to f
float c2f (float c)
{
  float f = ((9 * c )/ 5) + 32;
  return f;
} // c2f

// method from f to c
float f2c (float f)
{
  float c = ((f - 32)*5)/9;
  return c;
} // f2c

// main method
int main (int argc, char *argv[])
{
  // float input which is tempreture
  float input;
  int count;

  // check if arg = 3
  if (argc != 3)
  {
    printf("The wrong number of parameters have been supplied");
    exit(1);
  }
  // check c and f
  if (!((strcmp(argv[1], "-f") == 0) || (strcmp(argv[1], "-c")==0)))
  {
      printf("Failed to supply either -f or -c as the first option");
      exit(2);

  }
   // check the malformed number
  sscanf(argv[2], "%f%n", &input, &count);
  if(count != strlen(argv[2]))
  {
    printf("Malformed number in second parameter");
    exit(3);
  } // if

  // if it is f and tempreture is okay call method
  if (strcmp(argv[1], "-f") == 0)
  {
    if (input > -546.3){
      float celsius = f2c(input);
      printf("%.2f °C = %.2f °F \n", celsius, input);}
    else
    {
      printf("Temperatures below absolute zero");
      exit(4);
    }

  }
  //if it is c and tempreture is okay call method
  else if (strcmp(argv[1], "-c")== 0)
  {
    if (input > -273.15){
      float fahrenheit = c2f(input);
      printf("%.2f °C = %.2f °F \n", input, fahrenheit);}
    else{
      printf("Temperatures below absolute zero");
      exit(4);
    }
  }
  // return 0 at the end
  return 0;
} // main
