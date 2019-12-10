#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "global.h"
#include "bstree.h"


// Can be redefined if Value_Type changes
int compare(Value_Type a, Value_Type b){
  return strcmp(a,b);
} // compare

// tree is set as null i the start
struct bstree* initialize_set (int size)
{
  // An empty tree is represented by NULL
  return NULL;
} // initialize_set

// free all memory allocated for any tree
void tidy(struct bstree* tree)
{
  if(tree){
    tidy(tree->left);
    tidy(tree->right);
    // assumes tree owns value memory
    free(tree->value);
    free(tree);
  } // if
} // tidy
// function to get height
// first using method size
// then get left and right height by calculating for tree left and right
// whichever is bigger is ised and 1 is added for the height of the current node
int calc_height(struct bstree* tree)
{
  if (size(tree))
  {
    int left_height = calc_height(tree->left);
    int right_height = calc_height(tree->right);
    if (left_height >= right_height)
    {
      return left_height + 1;
    } // if
    else
      return right_height + 1;
  } // if
  else
    return 0;
} // calc_height
// gets size of the tree by checking if tree is present and then gettingleft and right then add 1.
//it is recursive
int size(struct bstree* tree){
  if(tree){
    return 1 + size(tree->left) + size(tree->right);
  } // if
  return 0;
} // size

// insert the value given into the tree by first checking if tree is there
// check where to put by comparing its value to the current tree values
struct bstree* insert (Value_Type value, struct bstree* tree)
{
  if(tree){
    if(compare(value, tree->value) > 0)
    {
      tree->comparisons++;
      tree->right = insert(value, tree->right);
    } // if
    else if (compare(value, tree->value) < 0)
    {
      tree->comparisons++;
      tree->left = insert(value, tree->left);
    } // else if
  } // if
  else{
    // if tree is noot there create a new one
    // TODO otherwise create a new node containing the value
    struct bstree* tree1 = malloc(sizeof(struct bstree));
    tree1->value  = strdup(value);
    tree1->left = NULL;
    tree1->right = NULL;
    tree1->height = 0;
    tree1->comparisons = 0;
    tree = tree1;
  } // else
  tree->height = calc_height(tree);
  //print_stats(tree);
  return tree;
} // insert

// gets the value we want from the tree
// by checking firstif the tree is present
// keep comparing untill u reach the end of tree if not found
// if found it reports true
bool find (Value_Type value, struct bstree* tree)
{
  if(tree){
    //TODO complete the find function
    while(tree != NULL)
    {
      if(compare(value, tree->value) == 0)
      {
        return true;
      }
      else if(compare(value, tree->value) < 0)
      {
        tree->comparisons++;
        return find(value, tree->left);
      }
      else
      {
        tree->comparisons++;
        return find(value, tree->right);
      } // els e
    } // while
  } // if
  // if tree is NULL then it contains no values
  else
    return false;
} // find 

// You can update this if you want
// this method is used to print the tree with its depth recursively
void print_set_recursive(struct bstree* tree, int depth)
{
  if(tree){
    for(unsigned i=0;i<depth;i++){ printf(" "); }
    printf("%s\n",tree->value);
    print_set_recursive(tree->left,depth+1);
    print_set_recursive(tree->right,depth+1);
  } // if
} // print_set_recursive
// You can update this if you want
void print_set (struct bstree* tree)
{
 printf("Tree:\n");
 print_set_recursive(tree,0);
} // print_set
// print the number of comparisons and the height of the tree
void print_stats (struct bstree* tree)
{
  printf("Height of the tree is : %d\n", tree->height);
  printf("Comparisons of the tree is : %d\n", tree->comparisons);
} // print_stats
