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
		Returns a $G_{n,p}$ random graph, also known as an Erdős-Rényi graph
    or a binomial graph.
    The $G_{n,p}$ model chooses each of the possible edges with probability $p$.

    Parameters
    ----------
    n : int
        The number of nodes.
    p : double
        Probability for edge creation.
    directed : bool, optional (default=False)
        If True, this function returns a directed graph.

    This algorithm [2]_ runs in $O(n^2)$ time.  
*/

graph erdos_renyi_random_graph(int n, double p, bool directed){
	std::vector < std::vector<int> > edges;
	std::vector <int> vertex(n);
	for(int i = 0; i < n; ++i) vertex[i] = i;
	if(directed) edges = permutations(vertex, 2);
	else edges = combinations(vertex, 2);
	graph res(n);
	if(p <= 0.0) return res;
	if(p >= 1.0) return complete_graph(n);


	for(int i = 0; i < edges.size(); ++i){
		if((rand()%100/(double)100) < p){
			res[edges[i][0]].push_back(edges[i][1]);
			if(not directed) res[edges[i][1]].push_back(edges[i][0]);
		}
	}
	return res;
}

/*
	Returns edge list of node pairs within 'radius' of each other
  using Minkowski distance metric 'p'
  Works 'O(n^2)' time
*/
void slow_edges(graph& G,const std::map <int, std::vector<double>>& pos, double radius, double p, int dim){
	auto combi = combinations_map(pos,2);
	for(int i = 0; i < combi.size(); ++i){
		double sum = 0.0;
		for(int j = 0; j < dim; ++j) sum += pow(abs(combi[i][0].second[j]-combi[i][1].second[j]), p);
		if(sum <= pow(radius, p)){
			G[combi[i][0].first].push_back(combi[i][1].first);
			G[combi[i][1].first].push_back(combi[i][0].first);
		}
	}
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

  Returns
  -------
  Graph
      A random geometric graph, undirected and without self-loops.
*/
graph random_geometric_graph(int n, double radius, int dim, double p){
	int n_name = n;
	graph G(n);
	std::map <int, std::vector <double>> pos;

	for(int i = 0; i < n; ++i){
		std::vector <double> pos_aux;
		for(int j = 0; j < dim; ++j) pos_aux.push_back((rand()%100/(double)100));
		pos[i] = pos_aux;
	}
	std::map <int, std::vector<double>>::iterator it;
	slow_edges(G, pos, radius, p, dim);
	return G;
}
