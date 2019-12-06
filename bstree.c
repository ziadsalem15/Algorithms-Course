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
}


struct bstree* initialize_set (int size)
{
  // An empty tree is represented by NULL
  return NULL;
}

void tidy(struct bstree* tree)
{
  if(tree){
    tidy(tree->left);
    tidy(tree->right);
    // assumes tree owns value memory
    free(tree->value);
    free(tree);
  }
}
int calc_height(struct bstree* tree)
{
  if (size(tree))
  {
    int left_height = calc_height(tree->left);
    int right_height = calc_height(tree->right);
    if (left_height >= right_height)
    {
      return left_height + 1;
    }
    else
      return right_height + 1;
  }
  else
    return 0;
}
int size(struct bstree* tree){
  if(tree){
    return 1 + size(tree->left) + size(tree->right);
  }
  return 0;
}

struct bstree* insert (Value_Type value, struct bstree* tree)
{
  if(tree){
    if(compare(value, tree->value) > 0)
    {
      tree->comparisons++;
      tree->right = insert(value, tree->right);
    }
    else if (compare(value, tree->value) < 0)
    {
      tree->comparisons++;
      tree->left = insert(value, tree->left);
    }
  }
  else{
    // TODO otherwise create a new node containing the value
    struct bstree* tree1 = malloc(sizeof(struct bstree));
    tree1->value  = strdup(value);
    tree1->left = NULL;
    tree1->right = NULL;
    tree1->height = 0;
    tree1->comparisons = 0;
    tree = tree1;
  }
  tree->height = calc_height(tree);
  //print_stats(tree);
  return tree;
}

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
      }
    }
  }
  // if tree is NULL then it contains no values
  else
    return false;
}

// You can update this if you want
void print_set_recursive(struct bstree* tree, int depth)
{
  if(tree){
    for(unsigned i=0;i<depth;i++){ printf(" "); }
    printf("%s\n",tree->value);
    print_set_recursive(tree->left,depth+1);
    print_set_recursive(tree->right,depth+1);
  }
}
// You can update this if you want
void print_set (struct bstree* tree)
{
 printf("Tree:\n");
 print_set_recursive(tree,0);
}

void print_stats (struct bstree* tree)
{
  //printf("Height of the tree is : %d\n", tree->height);
  //printf("Comparisons of the tree is : %d\n", tree->comparisons);
}
