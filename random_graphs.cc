#include "random_graphs.hh"



/* 
		Return the complete graph 'K_n' with n nodes.
    Parameters
    ----------
    n : int 
        number of nodes.
*/
graph complete_graph(int n){
	graph res(n);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(j != i) res[i].push_back(j);
		}
	}
	return res;
}

/*
		Returns a $G_{n,p}$ random undirected graph, also known as an Erdős-Rényi graph
    or a binomial graph.
    The $G_{n,p}$ model chooses each of the possible edges with probability $p$.

    Parameters
    ----------
    n : int
        The number of nodes.
    p : double
        Probability for edge creation.
		edge_fixed : bool, optional (default = False)
  	  true if we want get an edge number fixed graph
    Edges : int, optional if not n_fixed (default = 0)
  	  indicate the number of edges that we want the graph to have


    This algorithm [2]_ runs in $O(n^2)$ time.  
*/

graph erdos_renyi_random_graph(int n, double p, bool edge_fixed, int Edges){
	vector <int> vertex(n);
	for(int i = 0; i < n; ++i) vertex[i] = i;
	graph res(n);
	if(p <= 0.0) return res;
	if(p >= 1.0) return complete_graph(n);
	if (!edge_fixed) {
		for(int i = 0; i < n; ++i){
			for(int j = i + 1; j < n; ++j){
				if((rand()%100/(double)100) < p){
					res[i].push_back(j);
					res[j].push_back(i);
				}
			}
		}
	}
	else {
		int added_edge = 0;
		vector < vector <bool> > added(n, vector <bool>(n,false));
		while (added_edge < Edges) {
			for(int i = 0; i < n and added_edge < Edges; ++i){
				for(int j = i + 1; j < n and added_edge < Edges; ++j){
					if(not added[i][j] and (rand()%100/(double)100) < p){
						res[i].push_back(j);
						res[j].push_back(i);
						added[i][j] = true;
						added[j][i] = true; //no fa falta pero per si de cas
						++added_edge;
					}
				}
			}
		}
	}
	return res;
}


/*
	Returns edge list of node pairs within 'radius' of each other
  using Minkowski distance metric 'p'
  Works 'O(n^2)' time
*/
void slow_edges(graph& G, const vector <vector<double>>& pos, double radius, double p, int dim, bool edge_fixed, int Edges){
	if (!edge_fixed) {
		for(int i = 0; i < pos.size(); ++i){
			for(int j = i + 1; j < pos.size(); ++j){
				double sum = 0;
				for(int k = 0; k < dim; ++k) sum += pow(pos[i][k] - pos[j][k], p);
				if(sum <= pow(radius, p)){
					G[i].push_back(j);
					G[j].push_back(i);
				}
			}
		}
	}

	// else {
	// 	int added_edge = 0;
	// 	vector <vector<bool> > added(pos.size(), vector <bool>(pos.size(),false));
	// 	while(added_edge < Edges){
	// 		for(int i = 0; i < pos.size() and added_edge < Edges; ++i){
	// 			for(int j = i + 1; j < pos.size() and added_edge < Edges; ++j){
	// 				if(not added[i][j]){
	// 					double sum = 0;
	// 					for(int k = 0; k < dim; ++k) sum += pow(pos[i][k] - pos[j][k], p);
	// 					if(sum <= pow(radius, p)){
	// 						G[i].push_back(j);
	// 						G[j].push_back(i);
	// 						added[i][j] = true;
	// 						added[j][i] = true; //no fa falta pero per si de cas
	// 						++added_edge;
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }
} 

/*
	Returns a random geometric graph in the unit cube of dimensions 'dim'.
  The random geometric graph model places 'n' nodes uniformly at
  random in the unit cube. Two nodes are joined by an edge if the
  distance between the nodes is at most 'radius'.
  Edges are determined using Minkowski distance.
  time complexity $O(n^2)$.
  Parameters
  ----------
  n : int 
      Number of nodes 
  radius: double
      Distance threshold value
  dim : int, optional
      Dimension of graph
  p : double, optional
      Which Minkowski distance metric to use.  'p' has to meet the condition
      '1 <= p <= infinity'.
      If this argument is not specified, the :math:'L^2' metric
      (the Euclidean distance metric), p = 2 is used.
      This should not be confused with the 'p' of an Erdős-Rényi random
      graph, which represents probability.
  edge_fixed : bool, optional (default = False)
  	  true if we want get an edge number fixed graph
  Edges : int, optional if not n_fixed (default = 0)
  	  indicate the number of edges that we want the graph to have

  Returns
  -------
  Graph
      A random geometric graph, undirected and without self-loops.
*/
graph random_geometric_graph(int n, double radius, int dim, double p, bool edge_fixed, int Edges){
	int n_name = n;
	graph G(n);
	vector < vector <double> > pos(n);
	for(int i = 0; i < n; ++i){
		vector <double> pos_aux;
		for(int j = 0; j < dim; ++j) pos_aux.push_back((rand()%100/(double)100));
		pos[i] = pos_aux;
	}
	slow_edges(G, pos, radius, p, dim, edge_fixed, Edges);
	return G;
}
