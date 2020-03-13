#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#include "general.h"
#include "sp_algorithms.h"
#include "hashmap.h"
#include "airports.h"
#include "pq.h"


void count_reachable(char const *code) {
  /**
   * Print out the number of airports reachable from airport code.
   * Also count the start airport itself!
   */
   //The DFS algorithm is a recursive algorithm that uses the idea of backtracking. ...
   //The basic idea is as follows: Pick a starting node and push all its adjacent nodes into a stack.
   //Pop a node from stack to select the next node to visit and push all its adjacent nodes into a stack.
  size_t count = 0;
  graph_t const *g = ap_get_graph();
  size_t N = graph_get_num_nodes(g);
  // set pred for predeccessor nodes and dist which acts as the weight forech node
  node_t *pred = CALLOC(node_t,N);
  weight_t *dist = CALLOC(weight_t,N);
  // we act with ids as if they are nodes
  node_t id = ap_get_id(code);
  // use pq here as stack
  DPQ_t *pq = DPQ_new(N);
  // initialize as befor ein pq
  for (int i = 0; i < N; i++)
  {
    dist[i] = weight_inf();
    pred[i] = INVALID_NODE;
  }
  // insert weight of id and inc count by one because we include start airport
  dist[id] = weight_of_int(0);
  DPQ_insert(pq, id, dist[id]);
 	count++;
  while(!DPQ_is_empty(pq))
  {
    // pop the first node and checl if we reached dist
    // we iterates over all successors of node u in graph g
    //use tgt->v and tgt->w to access target node and edge weight
    node_t min_node = DPQ_pop_min(pq);
    for (edge_tgt_t const *tgt=graph_succs_begin(g,min_node);tgt!=graph_succs_end(g,min_node);++tgt)
    {
      if (weight_is_inf(dist[tgt->v]))
      {
        // instead of adding weight in bfs we sub because we act with it as a stack
        // so we need to make sure each time the weight is bigger than the previous time
        dist[tgt->v] = weight_sub(dist[min_node], weight_of_int(1));
        DPQ_insert(pq, tgt->v, tgt->w);
        count++;
      }
    }
  }
  DPQ_delete(pq);
  free(dist);
  free(pred);
  // Use this format!
  printf("%zu airports reachable from %s\n",count,code);
}

// a function I implemented which get the heuristics
weight_t* getH(graph_t const *g, node_t dist_node)
{
  size_t N = ap_get_num_ids();
  weight_t *h = calloc_fail(sizeof(weight_t),N);
  for(apid_t i = 0; i < N; i++)
  {
    // check if id is vlaid of airport
    if(ap_is_valid_id(i))
    {
      // we consider H as the distance of ap
      h[i] = ap_get_dist(i,dist_node);
    }
  }
  return h;
}

void compute_route(char const *algo, char const *scode, char const *dcode) {
  // set nodes, set g, result of astar, path
  node_t s=ap_get_id(scode);
  node_t d=ap_get_id(dcode);
  graph_t const *g = ap_get_graph();
  sp_result_t *result_sp = NULL;
  path_t* path = NULL;
  unsigned long long stat_edges_relaxed=0;

  /** Compute a shortest route between s and d, using the specified algorithm!
   *  "bfs" should compute a route with minimal hops, all other algorithms compute a route with minimal mileage
   */

   // for each algorithm we give its parameters and save the result returned
   // we get the path from answer
   // we get the no of relaxed edges
   // we dlete result at the ned for memory issues
   // in astar we will need to call getH func first to pass it to the algo 
  if (strcmp(algo,"bellman-ford")==0)
  {
    sssp_result_t *result = bellman_ford(g,s);
    if(weight_is_finite(result->dist[d]))
    {
      path = path_from_pred(result->pred, d);
    }
    stat_edges_relaxed = result->relax_count;
    sssp_result_delete(result);
  }
  else if (strcmp(algo,"dijkstra")==0)
  {
    sssp_result_t *result = dijkstra(g,s,d);
    if(weight_is_finite(result->dist[d]))
    {
      path = path_from_pred(result->pred,d);
    }
    stat_edges_relaxed = result->relax_count;
    sssp_result_delete(result);
  }
  else if (strcmp(algo,"astar")==0)
  {
    weight_t* h = getH(g,d);
    result_sp = astar_search(g,s,d,h);
    if(weight_is_finite(result_sp->dist))
    {
      path = result_sp->path;
    }
    stat_edges_relaxed = result_sp->relax_count;
    free(h);
  }
  else if (strcmp(algo,"bfs")==0)
  {
    sssp_result_t *result = bfs(g,s,d);
    if(weight_is_finite(result->dist[d]))
    {
      path = path_from_pred(result->pred,d);
    }
    stat_edges_relaxed = result->relax_count;
    sssp_result_delete(result);
  }
  else error("Invalid algorithm name: %s", algo);

  /**
   * Output one line per hop, indicating source, destination, and length.
   * Finally, output the total length
   */
   // if result we calcurlated is valid
   if(path != NULL)
   {
     weight_t tot_weights = weight_zero();
     for(size_t i = 0; i < path_len(path)-1; i++)
     {
       // we get the nodes for the current and next one
       // we get he code for current and next node
       node_t id_1st = path_get(path,i);
       char * code_1st = ap_get_code(id_1st);
       node_t id_next = path_get(path,i+1);
       char * code_next = ap_get_code(id_next);
       // get difference of dist
       weight_t diffDist = ap_get_dist(id_1st,id_next);
       printf("%s to %s (%ldkm)\n",code_1st,code_next,(long)weight_to_int(diffDist));
       // we add total weight each time
       tot_weights = weight_add(tot_weights,diffDist);
     }
     printf("Total = %ldkm\n",weight_to_int(tot_weights));
  }
  else
  {
    /// If there is no route ...
    printf("No route from %s to %s\n",scode,dcode);
  }
  // printf("%s to %s (%ldkm)\n","MAN","HEL",(long)1812);
  // printf("%s to %s (%ldkm)\n","HEL","HKG",(long)7810);
  // printf("%s to %s (%ldkm)\n","HKG","SYD",(long)7394);
  // printf("Total = %ldkm\n",(long)17016);


  /// And, in any case, log the number of relaxed/explored edges
  msg0("relaxed %llu edges\n", (unsigned long long)stat_edges_relaxed);

  // free for memory leaka s
  if(strcmp(algo,"astar")==0)
  {
    sp_result_delete(result_sp);
  }
  else{
    path_delete(path);
  }
}


int main(int argc, char **argv)
{

  ap_std_init();

  if (argc==5 && strcmp(argv[1],"route")==0) compute_route(argv[2],argv[3],argv[4]);
  else if (argc==3 && strcmp(argv[1],"count")==0) count_reachable(argv[2]);
  else error("Invalid command line");

  ap_delete();

  return 0;
}
