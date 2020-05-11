#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <fenv.h>
#include <time.h>
#include <gmp.h>

// r used in the program stands for result
// the hcf of a and b is calculated and stored inside r
void hcf(mpz_t a, mpz_t b, mpz_t r) {
  mpz_gcd(r, a, b);
}


void fme(mpz_t r, mpz_t g, mpz_t x, mpz_t p) {
  mpz_powm(r, g, x, p);
}

void imp(mpz_t r, mpz_t y, mpz_t p) {
  mpz_t pSub2;
  mpz_init(pSub2);
  mpz_sub_ui(pSub2, p, 2);
  mpz_powm(r, y, pSub2, p);
}

// helper function for generating a random number
void random_generator(mpz_t k, mpz_t p) {
  mpz_set_str(k, "0", 10);
  gmp_randstate_t random_state;
  gmp_randinit_mt(random_state);

  while(mpz_cmp_d(k, 1) < 0){
    mpz_urandomm(k, random_state, p);
  }
}

int main(int argc, char **argv) {

    mpz_t a, b, primativeRoot, power, prime, returnOfMethods, message, random, s, sInv;
    mpz_inits(a, b, power, returnOfMethods, message, random, s, sInv, NULL);
    char choice;
    mpz_init_set_ui(primativeRoot,43);                  // Initialize g and p
    mpz_init_set_str(prime,"170141183460469231731687303715884105727", 10);
    printf("Prime modulus is 170141183460469231731687303715884105727\n");
    printf("Primitive root wrt 170141183460469231731687303715884105727 is 43\n");

    while(true) {
        printf("\nChoose: e (encrypt) | d (decrypt) |k (get public key) | x (exit)? ");
        scanf("%s", &choice);

        switch(choice) {
            case 'k':
                printf("Type private key: ");
                gmp_scanf("%Zd", power);
                if ((mpz_cmp_ui(power, 1) == 0 || mpz_cmp_ui(power, 1) > 0) && mpz_cmp(power,prime)<0) {
                  fme(returnOfMethods, primativeRoot, power, prime);
                  gmp_printf("Public key is: %Zd\n", returnOfMethods);
                }
                else
                  printf("The private key is out of range (1<= key < prime)\n");
                break;
            case 'e':
                printf("Type secret number to send: ");
                gmp_scanf("%Zd", message);
                if (mpz_cmp_ui(message, 1) >= 0 && mpz_cmp(message,prime) < 0)
                {
                  printf("Type recipient's public key: ");
                  gmp_scanf("%Zd", returnOfMethods);
                  random_generator(random, prime);
                  fme(a, primativeRoot, random, prime);
                  fme(b, returnOfMethods, random, prime);
                  mpz_mul(b, b, message);
                  mpz_mod(b, b, prime);
                  gmp_printf("The encrypted secret is: (%Zd, %Zd)\n", a, b);
                }
                break;
            case 'd':
                printf("Type the recieved message in the form (a,b): ");
                if (gmp_scanf(" (%Zd,%Zd)",a, b) == 2) {
                  if (mpz_cmp_ui(a, 1) >= 0 && mpz_cmp(b,prime) < 0) {
                    printf("Type in your private key: ");
                    gmp_scanf("%Zd", power);
                    imp(sInv, a, prime);
                    fme(s, sInv, power, prime);
                    mpz_mul(message,  s, b);
                    mpz_mod(message, message, prime);
                    gmp_printf("The decrypted secret is: %Zd\n", message);
                  }
                  else
                    printf("The message is is out of range (1<= a && b < prime)\n");
                }
                else
                  printf("The message is not in the form (a,b)\n");
                break;
            case 'x':
                return 0;
        }
    }

    return 0;
}
