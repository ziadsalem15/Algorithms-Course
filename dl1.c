#include <stdio.h>
#include <stdlib.h>
#include "elGamal.h"

/*
    Modular exponentiation is considered a one way function, because it can
    be computed quickly, but there is not quick way to compute its inverse
    which is the discrete logarithm (recovering x from y)
*/
// 1 <= y < p
// 1 <= x < p
// g^x = y (mod p)
unsigned long dl(unsigned long y,unsigned long g,unsigned long p)
{
    unsigned long y_mod_p = y % p;
    unsigned long g_power_x_mod_p;
    for (unsigned long x = 1; x < p; x++)
    {
        g_power_x_mod_p = fme(g, x, p);
        if (g_power_x_mod_p == y_mod_p)
            return x;
    }
}
