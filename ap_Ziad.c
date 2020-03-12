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
  size_t count = 0;
  graph_t const *g = ap_get_graph();
  size_t N = graph_get_num_nodes(g);
  node_t *pred = CALLOC(node_t,N);
  weight_t *dist = CALLOC(weight_t,N);
  node_t id = ap_get_id(code);
  DPQ_t *pq = DPQ_new(N);
  for (int i = 0; i < N; i++)
  {
    dist[i] = weight_inf();
    pred[i] = INVALID_NODE;
  }
  dist[id] = weight_of_int(0);
  DPQ_insert(pq, id, dist[id]);
  count++;
  while(!DPQ_is_empty(pq))
  {
    node_t min_node = DPQ_pop_min(pq);
    for (edge_tgt_t const *tgt=graph_succs_begin(g,min_node);tgt!=graph_succs_end(g,min_node);++tgt)
    {
      if (weight_is_inf(dist[tgt->v]))
      {
        dist[tgt->v] = weight_sub(dist[min_node], weight_of_int(1));
        DPQ_insert(pq, tgt->v, tgt->w);
        count++;
      }
    }
  }
  // Use this format!
  printf("%zu airports reachable from %s\n",count,code);
}

weight_t* getH(graph_t const *g, node_t dist_node)
{
  size_t N = ap_get_num_ids();
  weight_t *h = calloc_fail(sizeof(weight_t),N);
  for(apid_t i = 0; i < N; i++)
  {
    if(ap_is_valid_id(i))
    {
      h[i] = ap_get_dist(i,dist_node);
    }
  }
  return h;

}
void compute_route(char const *algo, char const *scode, char const *dcode) {
  node_t s=ap_get_id(scode);
  node_t d=ap_get_id(dcode);
  graph_t const *g = ap_get_graph();
  sp_result_t *result_sp = NULL;
  path_t* path = NULL;
  unsigned long long stat_edges_relaxed=0;

  /** Compute a shortest route between s and d, using the specified algorithm!
   *  "bfs" should compute a route with minimal hops, all other algorithms compute a route with minimal mileage
   */

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
   if(path != NULL)
   {
     weight_t tot_weights = weight_zero();
     for(size_t i = 0; i < path_len(path)-1; i++)
     {
       node_t id_1st = path_get(path,i);
       char * code_1st = ap_get_code(id_1st);
       node_t id_next = path_get(path,i+1);
       char * code_next = ap_get_code(id_next);
       weight_t diffDist = ap_get_dist(id_1st,id_next);
       printf("%s to %s (%ldkm)\n",code_1st,code_next,(long)weight_to_int(diffDist));
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

  if(strcmp(algo,"astar")==0)
    sp_result_delete(result_sp);
  else
    path_delete(path);
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
