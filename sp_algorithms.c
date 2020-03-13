#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>

#include "graph.h"
#include "pq.h"
#include "sp_algorithms.h"

//Breadth-first search is an algorithm for traversing or searching tree
//or graph data structures. It starts at the tree root,
//and explores all of the neighbor nodes at the present depth prior to
//moving on to the nodes at the next depth level.
sssp_result_t *bfs(graph_t const *g, node_t src, node_t dst) {
  unsigned long long stat_edges_explored=0;
  size_t N = graph_get_num_nodes(g);
  // set pred for predeccessor nodes and dist which acts as the weight forech node
  node_t *pred = CALLOC(node_t,N);
  weight_t *dist = CALLOC(weight_t,N);
  // we will need pq here
  DPQ_t *pq = DPQ_new(N);
  // initialize wights and nodes as before in pq
  for (int i = 0; i < N; i++)
  {
    dist[i] = weight_inf();
    pred[i] = INVALID_NODE;
  }
  // set the weight of src as zero, insert it in pq, set the pred of src as src
  dist[src] = weight_zero();
  DPQ_insert(pq, src, dist[src]);
  pred[src] = src;
  //stat_edges_explored++;
	weight_t curr_weight = weight_zero();
  /* add src to end of graph */
  while(!DPQ_is_empty(pq))
  {
    // pop the first node and checl if we reached dist
    node_t min_node = DPQ_pop_min(pq);
    if (min_node == dst)
    {
      break;
    }
    // we iterates over all successors of node u in graph g
    //use tgt->v and tgt->w to access target node and edge weight
    for (edge_tgt_t const *tgt=graph_succs_begin(g,min_node);tgt!=graph_succs_end(g,min_node);++tgt)
    {
      // if we didn't access it before
      if (weight_is_inf(dist[tgt->v]))
      {
        // curr weight is inc by one bec we want to cancel the effect of priority
        // so we deal withit as distance which inc by one each time
        // set the weight of curr succ and set the pred as tyhe node we just popped
        // check is node is at dst again
        // insert
        stat_edges_explored++;
				curr_weight = weight_add(curr_weight, weight_of_int(1));
        dist[tgt->v] = weight_add(dist[min_node], weight_of_int(1));
        pred[tgt->v] = min_node;
				if (tgt->v == dst)
				{
					break;
				}
        DPQ_insert(pq, tgt->v, curr_weight);
      }
    }
  }
  // delete pq at end to avoid leaks
  DPQ_delete(pq);
  return sssp_result_new(N,src,dst,false,pred,dist,stat_edges_explored);
}

//The Bellman–Ford algorithm is an algorithm that computes shortest paths
//from a single source vertex to all of the other vertices in a weighted digraph
sssp_result_t *bellman_ford(graph_t const *g, node_t src) {
  unsigned long long stat_edges_explored=0;
  size_t N = graph_get_num_nodes(g);
  // set pred for predeccessor nodes and dist which acts as the weight forech node
  // initialize wights and nodes as before in pq
  // set the weight of src as zero,  set the pred of src as src
  weight_t *dist = CALLOC(weight_t,N);
  node_t *pred = CALLOC(node_t,N);
  for (int i = 0; i < N; i++)
  {
    dist[i] = weight_inf();
    pred[i] = INVALID_NODE;
  }
  dist[src] = weight_zero();
  pred[src] = src;
  //stat_edges_explored++;
  // bolesan to use to know when we should break
  bool have_changed = false;
  // used pseudo code given
  // we use three for loops to get eachnode and edge
  for (int i = 1; i <= N - 1; i++)
  {
    have_changed = false;
    for (node_t j = 0; j < N; j++)
    {
      // we iterates over all successors of node u in graph g
      //use tgt->v and tgt->w to access target node and edge weight
      for (edge_tgt_t const *tgt=graph_succs_begin(g, j);tgt!=graph_succs_end(g, j);++tgt)
      {
        // temp weight which is add of curr plus succ weight less than the succ weight
        if (!weight_is_inf(dist[j]) && weight_less(weight_add(dist[j], tgt->w), dist[tgt->v]))
        {
          // we set dist as we want by weight of current node plus the succ weight
          // set pred
					stat_edges_explored++;
          dist[tgt->v] = weight_add(dist[j], tgt->w);
          pred[tgt->v] = j;
          have_changed = true;
        }
      }
    }
    // if any time in the loop it didn'tchaneg we go out
    if(!have_changed)
    {
      break;
    }
  }
  // bool to return in the result as required
  // two for loops top handle neg values
  // I set them to neg inf whenever seen
  bool have_changed1 = false;
  for (node_t j = 0; j < N; j++)
  {
    for (edge_tgt_t const *tgt=graph_succs_begin(g, j);tgt!=graph_succs_end(g, j);++tgt)
    {
      if (!weight_is_inf(dist[j]) && weight_less(weight_add(dist[j], tgt->w), dist[tgt->v]))
      {
				stat_edges_explored++;
        dist[tgt->v] =  weight_neg_inf();
        have_changed1 = true;
      }
    }
  }
  return sssp_result_new(N,src,INVALID_NODE,have_changed1,pred,dist,stat_edges_explored);
}

//Dijkstra's algorithm is an algorithm for
//finding the shortest paths between nodes in a graph, which may represent, for example, road networks
sssp_result_t *dijkstra(graph_t const *g, node_t src, node_t dst) {
  unsigned long long stat_edges_explored=0;

  size_t N = graph_get_num_nodes(g);
  // set pred for predeccessor nodes and dist which acts as the weight forech node
  // we will need pq here
  // set the weight of src as zero, insert it in pq, set the pred of src as src
  node_t *pred = CALLOC(node_t,N);
  weight_t *dist = CALLOC(weight_t,N);
  DPQ_t *pq = DPQ_new(N);
  // set the weight of src as zero, insert it in pq, set the pred of src as src
  dist[src] = weight_zero();
  pred[src] = src;
  //stat_edges_explored++;
  // initialize wights and nodes as before in pq
  // insert every element in pq initially
  for (int i = 0; i < N; i++)
  {
    if (i != src)
    {
      dist[i] = weight_inf();
      pred[i] = INVALID_NODE;
    }
    DPQ_insert(pq, i, dist[i]);
  }
  while(!DPQ_is_empty(pq))
  {
    // pop the first node and checl if we reached dist
    node_t min_node = DPQ_pop_min(pq);
    if (min_node == dst)
    {
      break;
    }
    // we iterates over all successors of node u in graph g
    //use tgt->v and tgt->w to access target node and edge weight
    for (edge_tgt_t const *tgt=graph_succs_begin(g,min_node);tgt!=graph_succs_end(g,min_node);++tgt)
    {
      // we use the for loop we used in bellman again where we check weight temp of dist[min_node], tgt->w less than dist[tgt->v]
      if (!weight_is_inf(dist[min_node]) && weight_less(weight_add(dist[min_node], tgt->w), dist[tgt->v]))
      {
        // set dist as temp weight
        // pred is the node we just pooped
        // check if we reached dst
				stat_edges_explored ++;
        dist[tgt->v] = weight_add(dist[min_node], tgt->w);
        pred[tgt->v] = min_node;
				if (tgt->v == dst)
				{
					break;
				}
        // we dec key of the node we edited to be popped in the next loop
        DPQ_decrease_key(pq, tgt->v, dist[tgt->v]);
      }
    }
  }
  DPQ_delete(pq);
  return sssp_result_new(N,src,dst,false,pred,dist,stat_edges_explored);
}
//* @pre h is monotone, i.e., for all u, h(u) + w(u,v) <= h(v)

//A* is a graph traversal and path search algorithm, which is often used in computer science due to its completeness, optimality,
//and optimal efficiency. One major practical drawback is its space complexity,
//as it stores all generated nodes in memory.
sp_result_t *astar_search(graph_t const *g, node_t src, node_t dst, weight_t const* h) {
  unsigned long long stat_edges_explored=0;

  size_t N = graph_get_num_nodes(g);
  // set pred for predeccessor nodes and dist which acts as the weight forech node
  // we will need pq here
  // set the weight of src as zero, insert it in pq, set the pred of src as src
  node_t *pred = CALLOC(node_t,N);
  weight_t *dist = CALLOC(weight_t,N);
  DPQ_t *pq = DPQ_new(N);
  // set the weight of src as zero, insert it in pq, set the pred of src as src
  dist[src] = weight_zero();
  pred[src] = src;
  //stat_edges_explored++;
  //stat_edges_explored++;
  // initialize wights and nodes as before in pq
  // insert every element in pq initially
  for (int i = 0; i < N; i++)
  {
    if (i != src)
    {
      dist[i] = weight_inf();
      pred[i] = INVALID_NODE;
    }
    DPQ_insert(pq, i, dist[i]);
  }
  while(!DPQ_is_empty(pq))
  {
    // pop the first node and checl if we reached dist
    node_t min_node = DPQ_pop_min(pq);
    if (min_node == dst)
    {
      break;
    }
    // we iterates over all successors of node u in graph g
    //use tgt->v and tgt->w to access target node and edge weight
    for (edge_tgt_t const *tgt=graph_succs_begin(g,min_node);tgt!=graph_succs_end(g,min_node);++tgt)
    {
      // we check as before but when we also add the heuristics as temp weight to compare to weight of succ
      // the H is used to control astar behaviour
      if (!weight_is_inf(dist[min_node]) && weight_less(weight_add(weight_add(dist[min_node], tgt->w), h[min_node]), dist[tgt->v]))
      {
        // set dist as temp weight
        // pred is the node we just pooped
        // check if we reached dst
				stat_edges_explored++;
        dist[tgt->v] = (weight_add(dist[min_node], tgt->w));
        pred[tgt->v] = min_node;
				if (tgt->v == dst)
				{
					break;
				}
        // we dec key to popped later but we add the heuristics weights of node 
        DPQ_decrease_key(pq, tgt->v, weight_add(dist[tgt->v], h[tgt->v]));
      }
    }
  }
  DPQ_delete(pq);
  return sssp_to_sp_result(sssp_result_new(N,src,dst,false,pred,dist,stat_edges_explored), dst);
}
