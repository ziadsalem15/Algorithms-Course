#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>

#include "general.h"
#include "graph.h"
#include "pq.h"


/**
 * Implement the interface given in pq.h.
 *
 * We make a few proposals here, but you are welcome to deviate from that, as long as you
 * correctly implement the interface with the specified worst-case complexities!
 *
 */



/**
 * First, we propose a 1-based indexing into the heap, using 0 as "invalid index".
 *
 * Wrapping a heap-index into a structure prevents its accidental confusion with element indexes (Which might save you from a lot of hard-to-find bugs!).
 *
 */

typedef struct {size_t i;} hidx_t;


const hidx_t INVALID_HIDX = {0};
const hidx_t hidx_first = {1};

size_t idx_of(hidx_t i) {return i.i - 1;} /// Convert to zero-based index
bool hidx_is_invalid(hidx_t i) {return i.i == 0;}

// Index operations
hidx_t parent(hidx_t i) {return (hidx_t){i.i / 2}; }
hidx_t left(hidx_t i) {return (hidx_t){i.i * 2}; }
hidx_t right(hidx_t i) {return (hidx_t){i.i * 2 + 1}; }
bool has_parent(hidx_t i) {return parent(i).i>0; }
bool has_left(size_t n, hidx_t i) {return left(i).i<=n; }
bool has_right(size_t n, hidx_t i) {return right(i).i<=n; }

/**
 * The priority queue has 3 main components:
 *   1. An array D that maps nodes to priorities. It is independent from the content of the actual queue.
 *   2. An array H of nodes that encodes the heap of size heap_size.
 *   3. An array I, that maps each node to its current index in H. If a node u is not in the queue, we set I[u] = INVALID_HIDX.
 *
 */
struct _DPQ_t {
    size_t N;     // Number of elements
    size_t heap_size;    // Current size of heap
    weight_t *D;  // Priorities
    node_t *H;    // The heap
    hidx_t *I;    // Index of element in heap.
}_DPQ_t;


DPQ_t *DPQ_new(size_t N) {
    // Initialize the structure. Allocate enough space for all arrays to hold N elements.
    // allocate space for pq and its struct D, H , I
    // set len to N
    // set size to  0
    // Initialize weights to inf
    // initialize node to INVALID_NODE
    struct _DPQ_t* pq = malloc(sizeof(struct _DPQ_t));
    pq->N = N;
    pq->heap_size = 0;
    pq->D = calloc_fail(sizeof(weight_t), N);
    for (int i = 0; i < N; i++)
    {
      pq->D[i] = weight_inf();
    }
    pq->H = calloc_fail(sizeof(node_t), N);
    pq->I = calloc_fail(sizeof(hidx_t), N);
    for (int i = 0; i < N; i++)
    {
      pq->I[i] = INVALID_HIDX;
    }
    return pq;
}

void DPQ_delete(DPQ_t *pq) {
    // Free everything in pq
    free(pq->D);
    free(pq->H);
    free(pq->I);
    // and pq itself
    free(pq);
}

weight_t *DPQ_dist_free(DPQ_t *pq) {
  weight_t *res=pq->D;

  // Free everything but the D-array, which is returned
  free(pq->H);
  free(pq->I);
  // ...

  free(pq);
  return res;
}


weight_t DPQ_prio(DPQ_t const *pq, node_t u) {
  // Its a good idea to use assertions to ensure the preconditions!
  // This makes programs more likely to fail close to the reason of the error, rarher than later, when the (indirect) consequences become apparent.
  assert(u<pq->N);
  weight_t priority = pq->D[u];
  return priority; /// *** return priority of node u
}

/**
 * It is a good idea to wrap repetitive patterns into an own function (though, in C, it can be a pain).
 * This reduces the redundancy, and the chance of accidentally getting one of the repeated versions wrong.
 *
 * In this case, we get the priority associated with a heap index.
 */
weight_t _DPQ_hprio(DPQ_t const *pq, hidx_t i) {
    // get teh prio associated with heap index
    return DPQ_prio(pq,pq->H[idx_of(i)]);
}


void _DPQ_swap(DPQ_t *pq, hidx_t i, hidx_t j) {
  // Don't forget to update the I array!
  // save nodes at required index
  node_t nodeI = pq->H[idx_of(i)];
  node_t nodeJ = pq->H[idx_of(j)];
  // replace nodes at each index
  pq->H[idx_of(i)] = nodeJ;
  pq->H[idx_of(j)] = nodeI;

  // save index of one of them as temp
  // then sawap them around according to nodes
  hidx_t indexOfNodeI = pq->I[nodeI];
  pq->I[nodeI] = pq->I[nodeJ];
  pq->I[nodeJ] = indexOfNodeI;
}


void _DPQ_sift_up(DPQ_t *pq, hidx_t i) {
  while (true)
  {
    // if index is less than 0 return
    if (idx_of(i) <= 0)
    {
      return;
    }
    // get parent
    hidx_t parenti = parent(i);
    // if teh weight sis less than weight of parent swap
    if (weight_less(_DPQ_hprio(pq, i), _DPQ_hprio(pq, parenti))){
      _DPQ_swap(pq, i, parenti);
    }
    else{
      return;
    }
    // set current index as parent
    i = parenti;
  }

}

void _DPQ_sift_down(DPQ_t *pq, hidx_t i) {
  // Don't forget to handle the case that you end up at an index that has a left, but no right child!
  while (true)
  {
    // get left and right index
    hidx_t l_index = left(i);
    hidx_t r_index = right(i);
    // check index is not bigher than the boundaries right and left
    if (!has_left(pq->heap_size, i)&& !has_right(pq->heap_size, i)){
      return;
    }
    // satrt from the left by saving index
    hidx_t smallest = l_index;
    // compare indexes and check that the weight of right less than weight of left
    if (idx_of(r_index) < pq->heap_size && weight_less(_DPQ_hprio(pq, r_index), _DPQ_hprio(pq, l_index)))
    {
      smallest = r_index;
    }
    // swap if this temp weight i sless than the one we are given
    if(weight_less(_DPQ_hprio(pq, smallest) ,_DPQ_hprio(pq, i))){
      _DPQ_swap(pq,i,smallest);
    }
    else
    {
      return;
    }
    i = smallest;
  }
}

/**
 * Check if node is contained in queue
 *
 * Complexity: O(1)
 *
 * @pre u < N
 */
bool DPQ_contains(DPQ_t const *pq, node_t u) {
    assert(u<pq->N);
    // if thenode we are given is not incvalid then the it is present so return true
    // Use I to check if node is on heap
    if (pq->I[u].i != INVALID_HIDX.i){
      return true;
    }
    else
    {
      return false; // Use I to check if node is on heap
    }
}

/**
 * Insert node into queue, with given priority.
 * The priority of this node is set accordingly.
 *
 * Complexity: O(log N)
 *
 * @pre Node must not be in queue
 * @pre u < N
 * @param u node
 * @param w priority
 */
void DPQ_insert(DPQ_t *pq, node_t u, weight_t w) {
  // Insert at end, then sift up

  // Don't forget to update I!
  assert(u<pq->N);
  // increase size by one, insert the weight
  // insert node at the end
  // set index of node and then sift up
  pq->heap_size++;
  pq->D[u] = w;
  hidx_t size = {pq->heap_size};
  pq->H[idx_of(size)] = u;
  pq->I[u] = size;

  _DPQ_sift_up(pq, size);
}

bool DPQ_is_empty(DPQ_t const *pq) {return pq->heap_size==0;}

/**
 * Retrieve and remove an element of the queue with minimal priority
 *
 * Complexity: O(log N)
 *
 * @pre The queue is not empty
 */
node_t DPQ_pop_min(DPQ_t *pq) {
  assert(pq->heap_size>0);
  // Swap first with last element, decrement heap size, then sift down
  // Don't forget to update I!
  node_t node = pq->H[idx_of(hidx_first)];
  hidx_t last_index = {pq->heap_size};
  _DPQ_swap(pq, hidx_first, last_index);
  // dec size by pne , sift down to update queue
  pq->heap_size--;
  _DPQ_sift_down(pq, hidx_first);
  // set the idx of node we just popped to invalid
  pq->I[node] = INVALID_HIDX;
  return node; // Return the node that was removed
}

/**
 * Lower priority of element in queue
 *
 */
void DPQ_decrease_key(DPQ_t *pq, node_t u, weight_t w) {
  assert(u<pq->N);
  assert(DPQ_contains(pq,u));
  assert(weight_less(w, pq->D[u]));

  // Update priority, then sift up. Use I to find element's index on the heap
  pq->D[u] = w;
  hidx_t index = pq->I[u];
  _DPQ_sift_up(pq, index);

}
