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

sssp_result_t *bfs(graph_t const *g, node_t src, node_t dst) {
  unsigned long long stat_edges_explored=0;

  size_t N = graph_get_num_nodes(g);
  node_t *pred = CALLOC(node_t,N);
  weight_t *dist = CALLOC(weight_t,N);
  DPQ_t *pq = DPQ_new(N);
  for (int i = 0; i < N; i++)
  {
    dist[i] = weight_inf();
    pred[i] = INVALID_NODE;
  }
  dist[src] = weight_zero();
  DPQ_insert(pq, src, dist[src]);
  pred[src] = src;
  stat_edges_explored++;
  /* add src to end of graph */
  while(!DPQ_is_empty(pq))
  {
    node_t min_node = DPQ_pop_min(pq);
    for (edge_tgt_t const *tgt=graph_succs_begin(g,min_node);tgt!=graph_succs_end(g,min_node);++tgt)
    {
      if (weight_is_inf(dist[tgt->v]))
      {
        stat_edges_explored++;
        dist[tgt->v] = weight_add(dist[min_node], weight_of_int(1));
        pred[tgt->v] = min_node;
        DPQ_insert(pq, tgt->v, dist[tgt->v]);
        if (tgt->v == dst)
        {
          return sssp_result_new(N,src,dst,false,pred,dist,stat_edges_explored);
        }
      }
    }
  }

  return sssp_result_new(N,src,dst,false,pred,dist,stat_edges_explored);
}

sssp_result_t *bellman_ford(graph_t const *g, node_t src) {
  unsigned long long stat_edges_explored=0;
  size_t N = graph_get_num_nodes(g);
  weight_t *dist = CALLOC(weight_t,N);
  node_t *pred = CALLOC(node_t,N);
  for (int i = 0; i < N; i++)
  {
    dist[i] = weight_inf();
    pred[i] = INVALID_NODE;
  }
  dist[src] = weight_zero();
  pred[src] = src;
  stat_edges_explored++;
  bool have_changed = false;
  for (int i = 1; i <= N - 1; i++)
  {
    have_changed = false;
    for (node_t j = 0; j < N; j++)
    {
      for (edge_tgt_t const *tgt=graph_succs_begin(g, j);tgt!=graph_succs_end(g, j);++tgt)
      {
        if (!weight_is_inf(dist[j]) && weight_less(weight_add(dist[j], tgt->w), dist[tgt->v]))
        {
          dist[tgt->v] = weight_add(dist[j], tgt->w);
          pred[tgt->v] = j;
          have_changed = true;
          stat_edges_explored++;
        }
      }
    }
    if(!have_changed)
    {
      break;
    }
  }
  bool have_changed1 = false;
  for (node_t j = 0; j < N; j++)
  {
    for (edge_tgt_t const *tgt=graph_succs_begin(g, j);tgt!=graph_succs_end(g, j);++tgt)
    {
      if (!weight_is_inf(dist[j]) && weight_less(weight_add(dist[j], tgt->w), dist[tgt->v]))
      {
        dist[tgt->v] =  weight_neg_inf();
        have_changed1 = true;
        stat_edges_explored++;
      }
    }
  }
  return sssp_result_new(N,src,INVALID_NODE,have_changed1,pred,dist,stat_edges_explored);
}

sssp_result_t *dijkstra(graph_t const *g, node_t src, node_t dst) {
  unsigned long long stat_edges_explored=0;

  size_t N = graph_get_num_nodes(g);
  node_t *pred = CALLOC(node_t,N);
  weight_t *dist = CALLOC(weight_t,N);
  DPQ_t *pq = DPQ_new(N);
  dist[src] = weight_zero();
  pred[src] = src;
  stat_edges_explored++;
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
    node_t min_node = DPQ_pop_min(pq);
    if (min_node == dst)
    {
      break;
    }
    for (edge_tgt_t const *tgt=graph_succs_begin(g,min_node);tgt!=graph_succs_end(g,min_node);++tgt)
    {
      if (!weight_is_inf(dist[min_node]) && weight_less(weight_add(dist[min_node], tgt->w), dist[tgt->v]))
      {
        dist[tgt->v] = weight_add(dist[min_node], tgt->w);
        pred[tgt->v] = min_node;
        DPQ_decrease_key(pq, tgt->v, dist[tgt->v]);
      }
      stat_edges_explored ++;
    }
  }
  return sssp_result_new(N,src,dst,false,pred,dist,stat_edges_explored);
}
//* @pre h is monotone, i.e., for all u, h(u) + w(u,v) <= h(v)

sp_result_t *astar_search(graph_t const *g, node_t src, node_t dst, weight_t const* h) {
  unsigned long long stat_edges_explored=0;

  size_t N = graph_get_num_nodes(g);
  node_t *pred = CALLOC(node_t,N);
  weight_t *dist = CALLOC(weight_t,N);
  DPQ_t *pq = DPQ_new(N);
  dist[src] = weight_zero();
  pred[src] = src;
  stat_edges_explored++;
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
    node_t min_node = DPQ_pop_min(pq);
    if (min_node == dst)
    {
      break;
    }
    for (edge_tgt_t const *tgt=graph_succs_begin(g,min_node);tgt!=graph_succs_end(g,min_node);++tgt)
    {
      if (!weight_is_inf(dist[min_node]) && weight_less(weight_add(weight_add(dist[min_node], tgt->w), h[min_node]), dist[tgt->v]))
      {
        dist[tgt->v] = (weight_add(dist[min_node], tgt->w));
        pred[tgt->v] = min_node;
        DPQ_decrease_key(pq, tgt->v, weight_add(dist[tgt->v], h[tgt->v]));
      }
      stat_edges_explored++;
    }
  }

  return sssp_to_sp_result(sssp_result_new(N,src,dst,false,pred,dist,stat_edges_explored), dst);
}
