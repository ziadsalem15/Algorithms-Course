#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include <fenv.h>
#include <time.h>


unsigned long hcf(unsigned long a, unsigned long b);

unsigned long fme(unsigned long g,unsigned long x, unsigned long p);

unsigned long dl(unsigned long y, unsigned long g, unsigned long p);

unsigned long imp(unsigned long y, unsigned long p);

void menu(unsigned long g, unsigned long p);
void getPublicKey(unsigned long g, unsigned long p);

void encrypt(unsigned long g, unsigned long p);
void decrypt(unsigned long g, unsigned long p);

// Task 1 Finding the highest common factor
unsigned long hcf(unsigned long a, unsigned long b)
{

  if(a > b && a != 0)
   if(b == 0)
    return a;
   else
     return hcf(b, a % b);

  if(b > a && b != 0)
   if(a == 0)
    return b;
   else
     return hcf(a, b % a);

   return a;

}//hef

// Task 2 Fast modular exponential
unsigned long fme(unsigned long g,unsigned long x, unsigned long p)
{
  // The function is iterative and has linear growth as


  int d = 1;
  int bi = 0;

  int biNum[70];
  int n = x;


  // Fill in the bits
  while(n > 0)
  {
    biNum[bi] = n % 2;
    n = n / 2;
    bi++;
  }//whie

  int k = bi - 1;

  // Get the modular exponential based on bits
  for(int i = bi - 1; i >= 0; i--)
  {
    d = (d*d) % p;

    if ( biNum[k--] == 1)
      d = (d * g) % p;
  }//for

  return d;
}//fme

// Task 3 Discrete logarithm
// Modular exponential is considered a one way function because it is disproportionally easier to compute
// the y value from the x value, but it is way harder to compute the x value from y value
unsigned long dl(unsigned long y, unsigned long g, unsigned long p)
{
   for(unsigned long i = 1; i < p; i++)
   {
      unsigned long x = (unsigned long)pow(g, i) % p;
      if(y == x)
       return i;
   }//for

   //Error
   return -1;
}//dl

// Task 4 Inverse modulo prime
// linear time as hcf runs in that way and so does the fme which means n + n time
unsigned long imp(unsigned long y, unsigned long p)
{
  unsigned long g = hcf(y,p);
  if(g == 1)
   return fme(y, p-2,p);

  //Error
  return -1;
}//imp

// Method for the user interface
void menu(unsigned long g, unsigned long p)
{
 char option[sizeof(char)];
 printf("\nChoose: e (encrypt) |d (decrypt) |k (get public key) |x (exit)?");

 scanf("%s", option);

 if(strcmp(option, "k") == 0)
  getPublicKey(g,p);

 if(strcmp(option, "e") == 0)
  encrypt(g,p);

 if(strcmp(option, "d") == 0)
  decrypt(g,p);

 return;


}//menu

// Method that handles the "k" input
void getPublicKey(unsigned long g, unsigned long p)
{
   unsigned long key;
   printf("\nType private key: ");
   scanf("%lu", &key);
   unsigned long publicKey = fme(g, key, p);
   printf("\nPublic key is: %lu", publicKey);

   menu(g, p);

}//getPublicKey

// Method that handles the "e" input
void encrypt(unsigned long g, unsigned long p)
{

   unsigned long secretNumber;
   unsigned long key;


   printf("\nType secret number to send: ");
   scanf("%lu", &secretNumber);

   printf("\nType recipent’s public key: ");
   scanf("%lu", &key);

   srand(time(NULL));
   unsigned long k = (rand() + 1) % p;

   // Encrypt into the secret numbers in (a,b) format
   unsigned long a = fme(g, k, p);
   unsigned long b = (secretNumber * fme(key, k, p)) % p;

   printf("\nEncrypted secret is (%lu, %lu)\n", a, b);

   menu(g, p);
}//encrypt

void decrypt(unsigned long g, unsigned long p)
{
  char* recMessage[sizeof(char*)];
  unsigned long privateKey;

  printf("\nType in received message in form(a,b): ");
  scanf("%s", recMessage);

  printf("\nType in your private key: ");

  scanf("%lu", &privateKey);

  //printf("dejekeihdi\n");

  // Transform the (a,b) format into unsigned long so they can be used
  char *po = recMessage;
  po++[strlen(po)] = 0;

  char* firstPart = strtok(po, ",");
  char* secondPart = strtok(NULL, ",");

  // From string to unsigned long
  unsigned long a = strtoul(firstPart, NULL, 10);
  unsigned long b = strtoul(secondPart, NULL, 10);

  // Get the decrypted secret
  unsigned long publicKey = fme(a, privateKey, p);
  unsigned long inverse = imp(publicKey, p);
  unsigned long decryptedSecret = b * inverse % p;

  printf("The decrypted secret is :%lu\n", decryptedSecret);

  menu(g, p);

}//decrypt


// Main method
int main(int argc, char **argv)
{
  unsigned long g = 3;
  unsigned long p = 65537;


  printf("Prime modulus is %d\n", p);
  printf("Primitive root wrt %d is %d\n", p,g);
  menu(g, p);

}//main
