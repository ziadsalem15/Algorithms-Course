
// Dynamic programming for 0/1 knapsack
// (C) Joshua Knowles
// The variable names here follow standard usage in formulating
// dynamic programming via recursive definitions

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

FILE *fp;  // file pointer for reading the input files
int Capacity;     // capacity of the knapsack (total weight that can be stored)
int Nitems;    // number of items available
int *item_weights;  // vector of item weights
int *item_values;  // vector of item profits or values
int *temp_indexes;  // list of temporary item indexes for sorting items by value/weight
int QUIET=0; // this can be set to 1 to suppress output


// function prototypes
extern void read_knapsack_instance(char *filename);
int DP(int *v,int *wv, int n, int W, int *solution);
extern int check_evaluate_and_print_sol(int *sol,  int *total_value, int *total_weight);

int main(int argc, char *argv[1])
{
  int *solution;    // binary vector indicating items to pack
  int total_value, total_weight;  // total value and total weight of items packed

  read_knapsack_instance(argv[1]);

  if((solution = (int *)malloc((Nitems+1)*sizeof(int)))==NULL)
    {
      fprintf(stderr,"Problem allocating table for DP\n");
      exit(1);
    }

  DP(item_values,item_weights,Nitems,Capacity,solution);
  check_evaluate_and_print_sol(solution,&total_weight,&total_value);
  return(0);
}

int DP(int *v,int *wv, int n, int W, int *solution)
{

  // the dynamic programming function for the knapsack problem
  // the code was adapted from p17 of http://www.es.ele.tue.nl/education/5MC10/solutions/knapsack.pdf

  // v array holds the values / profits / benefits of the items
  // wv array holds the sizes / weights of the items
  // n is the total number of items
  // W is the constraint (the weight capacity of the knapsack)
  // solution: a 1 in position n means pack item number n+1. A zero means do not pack it.

  int **V;
  int **keep;  // 2d arrays for use in the dynamic programming solution
  // keep[][] and V[][] are both of size (n+1)*(W+1)

  int i, w, K;

  // Dynamically allocate memory for variables V and keep
  /* ADD CODE HERE */

  V = (int**) malloc(sizeof(int*) * (n+1));
  keep = (int**) malloc(sizeof(int*) * (n+1));
  //initialize V[w] and keep[w] by allocating memory for it
  for (w = 0; w <= W; w++)
  {
    V[w] = (int*) malloc(sizeof(int) * (W+1));
    keep[w] = (int*) malloc(sizeof(int) * (W+1));
  }

 //  set the values of the zeroth row of the partial solutions table to zero
  /* ADD CODE HERE */
  for (w = 0; w <= W; w++)
  {
    V[0][w] = 0;
  }


 // main dynamic programming loops , adding one item at a time and looping through weights from 0 to W
  /* ADD CODE HERE */
  // for loop over number and for loop over wieghts
  //
  for (i = 1; i <= n; i++)
  {
    for (w = 0; w <= W; w++)
    {
      // if current weight less than knapsack weight and checking on V
      if ((wv[i] <= w) && (v[i] + V[i - 1][w - wv[i]] > V[i - 1][w]))
      {
        // set V[i][w] = to current v added to V[i - 1][w - wv[i]]
        V[i][w] = v[i] + V[i - 1][w - wv[i]];
        // set keep to 1 which means it is included in th knapsack
        keep[i][w] = 1;
      }
      else
      {
        // if not don't put element
        V[i][w] = V[i - 1][w];
        keep[i][w] = 0;
      }
    }
  }

  // now discover which items were in the optimal solution
  /* ADD CODE HERE */
  // check on keep , if == 1 set solution = 1 and subtract current weight
  //of item from K
  K = W;
  for (i = n; i >= 1; i--)
  {
    if (keep[i][K] == 1)
    {
        solution[i] = 1;
        K = K - wv[i];
    }
  }

  return V[n][W];
}
