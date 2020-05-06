#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned long hcf(unsigned long a, unsigned long b) {
    if(b==0) {
        return a;
    } else {
        return hcf(b, a%b);
    }
}

/* 'Fast modular exponentiation'. This method runs in linear time as to number of operations in the loop
 * is log x base 2. Therefore complexity is O(2^(logx base 2))=O(x);
 */
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

unsigned long hcf(unsigned long a, unsigned long b)
{
  if (b == 0)
  {
    return a;
  }
  else
  {
    unsigned long r = a % b;
    hcf(b, r);
  }
}

/* This method returns inverse modulo prime, i.e. the value of x for which
 * x.y `= 1 mod p.
 */
unsigned long imp(unsigned long y, unsigned long p) {
  unsigned long g = hcf(y, p);
  if (g != 1)
  {
    printf("The modular inverse doesn't exist\n");
  }
  else
  {
    printf("The modular multiplicative inverse is %1u\n", fme(y, p-2, p));
  }

int main(int argc, char **argv) {


    /* a is first value of recieved message.
	   b is second value of recieved message.
	   g is primative root.
	   x is power.
	   p is prime.
	   y is return value of methods.
	   m is message.
	   k is a random number in rank 1-p
	 */

    unsigned long int a, b, g, x, p, y, m, k, s, sInv;
    char choice;
    p=65537;
    g=3;

    printf("Prime modulus is %lu\n", p);
    printf("Primitive root wrt %lu is %lu\n", p, g);


    while(true) {
        printf("\nChoose: e (encrypt) | d (decrypt) |k (get public key) | x (exit)? ");
        scanf("%s", &choice);

        switch(choice) {
            case 'k':
                printf("Type private key: ");
                scanf("%lu", &x);
                printf("Public key is: %lu\n", fme(g, x, p));
                break;
            case 'e':
                printf("Type secret number to send: ");
                scanf("%lu", &m);
                printf("Type recipient's public key: ");
                scanf("%lu", &y);
                k=rand()%(p-1)+1;
                a=fme(g, k, p);
                b=(m*fme(y, k, p))%p;
                printf("The encrypted secret is: (%lu, %lu)\n", a, b);
                break;
            case 'd':
                printf("Type the recieved message in the form (a,b): ");
                scanf("%lu %lu", &a, &b);
                printf("Type in your private key: ");
                scanf("%lu", &x);
                s=fme(a, x, p);
                sInv=imp(s, p);
                m=(sInv*b)%p;
                printf("The decrypted secret is: %lu\n", m);
                break;
            case 'x':
                return 0;
        }
    }

    return 0;
}
