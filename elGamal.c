#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <fenv.h>
#include <time.h>

unsigned long hcf(unsigned long a, unsigned long b) {
    if(b==0) {
        return a;
    } else {
        return hcf(b, a%b);
    }
}

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

/* This method returns inverse modulo prime, i.e. the value of x for which
 * x.y `= 1 mod p.
 */
unsigned long imp(unsigned long y, unsigned long p)
{
    return fme(y, p-2, p);
}

int main(int argc, char **argv) {

    unsigned long int a, b, primativeRoot, power, prime, returnOfMethods, message, random, s, sInv;
    char choice;
    prime=65537;
    primativeRoot=3;
    printf("Prime modulus is %lu\n", prime);
    printf("Primitive root wrt %lu is %lu\n", prime, primativeRoot);


    while(true) {
        printf("\nChoose: e (encrypt) | d (decrypt) |k (get public key) | x (exit)? ");
        scanf("%s", &choice);

        switch(choice) {
            case 'k':
                printf("Type private key: ");
                scanf("%lu", &power);
                printf("Public key is: %lu\n", fme(primativeRoot, power, prime));
                break;
            case 'e':
                printf("Type secret number to send: ");
                scanf("%lu", &message);
                printf("Type recipient's public key: ");
                scanf("%lu", &returnOfMethods);
                random=rand()%(prime-1)+1;
                a=fme(primativeRoot, random, prime);
                b=(message*fme(returnOfMethods, random, prime))%prime;
                printf("The encrypted secret is: (%lu,%lu)\n", a, b);
                break;
            case 'd':
                printf("Type the recieved message in the form (a,b): ");
                scanf(" (%lu,%lu)",&a, &b);
                printf("Type in your private key: ");
                scanf("%lu", &power);
                sInv=imp(a, prime);
                s=fme(sInv, power, prime);
                message=(s*b)%prime;
                printf("The decrypted secret is: %lu\n", message);
                break;
            case 'x':
                return 0;
        }
    }

    return 0;
}
