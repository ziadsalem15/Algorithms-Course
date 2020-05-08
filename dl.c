#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* This method returns the discrete log, i.e. the value of x for which y=g^x mod p. */

unsigned long fme(unsigned long g, unsigned long x, unsigned long p) {

    // Initialize result
    unsigned long s=1;

    // Update g if it is more than or
    // equal to p
    g = g % p;

    // In case g is divisible by p;
    if (g == 0) return 0;


    while(x > 0) {
        // If x is odd, multiply g with result
        if(x % 2 == 1) {
            s = (s * g) % p;
        }

        // x must be even now
        g = (g * g) % p;
        x = x / 2;
    }
    return s;
}
unsigned long dl(unsigned long y, unsigned long g, unsigned long p) {
    for (unsigned long i = 1; i < p; i++)
    {
      if (fme(g, i, p) == y)
      {
        return i;
      }
    }
    return 0;
}
