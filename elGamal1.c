#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <gmp.h>
#include "elGamal1.h"


int main(void)
{
    unsigned long p = 65537;
    unsigned long g = 3;
    char option[1];
    char c;

    // random generated number (k), in the range: 1 <= k < p
    unsigned long k = generate_random(1, p);

    do      // while not exit
    {
        printf("\nPlease choose an option:\n");
        printf("e (encrypt) | d (decrypt) |k (get public key) | x (exit):\n");
        scanf("%s", &option);

        if (strcmp(option, "e") == 0)   // encrypt
        {
            unsigned long M;
            unsigned long y;
            printf("Please enter a message (M) where: 1 <= M < %lu\n", p);
            scanf("%lu", &M);
            // M should be in the valid range
            if (!(M >= 1 && M < p))
            {
                printf("Your message isn't in the valid range\n");
                return -1;
            }
            printf("Please enter your public key (y) where: 1 <= y < %lu\n", p);
            scanf("%lu", &y);

            /*  SHOULD I CHECK IF Y IN THE VALID RANGE ?? */

            if (!(y >= 1 && y < p))
            {
                printf("Your message isn't in the valid range\n");
                return -1;
            }

            // compute elGamal encryption of M as integer pair (a, b)
            // a = g^k mod p
            unsigned long a = fme(g, k, p);
            // b = M * y^k mod p
            unsigned long b = (fme(y, k, p) * M) % p;

            printf("The encrypted secret: (%lu, %lu)\n", a, b);

        }
        else if (strcmp(option, "o") == 0)  // other / test
        {
            printf("%s\n", "decrypt");
            unsigned long y = 8388608;
            unsigned long p_other = 4093082899;
            unsigned long M = 30052019;
            unsigned long k = 1607207821;

            unsigned int ans1 = (fme(y, k, p_other) * M) % p_other;
            printf("ans1 = %u", ans1);

        }
        else if (strcmp(option, "d") == 0)  // decrypt
        {
            unsigned long a;
            unsigned long b;
            //char[1] seperator;
            printf("Type in recieved message in the form (a,b):\n");
            if (scanf(" (%lu,%lu)",&a, &b) != 2)
            {
                printf("Invalid format, use the format: (a,b)\n");
                return -1;
            }
            unsigned long x;
            printf("Type private key (x) in the range: 1 <= x < %lu : \n", p);
            scanf("%lu", &x);
            if (!(x >= 1 && x < p))
            {
                printf("private key is not in the given range\n");
                return -1;
            }

            unsigned long s = fme(a, x, p);
            unsigned long s_inverse = imp(s, p);
            unsigned long M = b * s_inverse % p;

            printf("Your message:\t%lu", M);


        }
        else if (strcmp(option, "k") == 0)  // get public key
        {
            // x is the private key
            unsigned long x;
            printf("Type private key (x) in the range: 1 <= x < %lu : \n", p);
            scanf("%lu", &x);

            // private key (x) must be in the range: 1 <= x < p
            if (x >= 1 && x < p)
            {
                // y is the elGamal public key = g^x mod p
                unsigned long y = fme(g, x, p);
                printf("Public key is:\t%lu\n", y);
            }
            else
            {
                printf("The private key you entered wasn't in the specified range\n");
                return -1;
            }

        }
        else if (strcmp(option, "x") == 0)  // exit
        {
            printf("%s\n", "exiting ...");
        }
        else    // invalid option
        {
            printf("Invalid option!\n");
            return -1;
        }


    }  while (strcmp(option, "x") != 0);


    return 0;
}



// This algorithm is linear in the size of algorithm
// based on the fact that: hcf(a, b) = hcf(b, a mod b)
// assuming: a >= b and a != 0
unsigned long hcf(unsigned long a,unsigned long b)
{
    if (b == 0)
        return a;
    else
        return hcf(b, a % b);

}

// Let p be a prime, and g a primitive root modulo p
// returns: g^x mod p
unsigned long fme(unsigned long g,unsigned long x, unsigned long p)
{
    unsigned long n = get_no_of_bits(x);
    unsigned long  d = 1;
    for (unsigned long i = n - 1; i != -1; i--)
    {
        d = (d * d) % p;
        if (is_bit_set(x, i))
            d = (d * g) % p;
    }
    return d;
}

// given y and p: it finds "x" the modular inverse of y
// st. x.y = 1 (mod p)
// 1 <= y < p
// 1 <= x < p
// This implementation is based fermat's little theorem
// Note: p is prime
unsigned long imp(unsigned long y, unsigned long p)
{
    return fme(y, p - 2, p);
}


// HELPER FOT FME
// returns: number of bits in a number.
unsigned long get_no_of_bits(unsigned long n)
{
   unsigned long count = 0;
   while (n)
   {
        count++;
        n >>= 1;
    }
    return count;
}

// HELPER FOR FME
// returns 1 if I-th bit in n is set, 0 otherwise
// k = 0 corresponds to the first bit
unsigned long is_bit_set(unsigned long n, unsigned long k)
{
    return n & (1 << k);
}

// HELPER
// returns a random unsigned int k, where low <= k < high
unsigned long generate_random(unsigned long low, unsigned long high)
{
    // we don't want high to be in the range
    high -= 1;
    return (rand() % (high - low + 1)) + low;
}
