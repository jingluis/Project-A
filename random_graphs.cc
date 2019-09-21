#include <iostream>
#include <vector>
#include "algorithms.hh"

using graph = std::vector < std::vector <int> >;

graph complete_graph(int n){
	graph res(n);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(j != i) res[i].push_back(j);
		}
	}
	return res;
}

graph erdos_renyi_random_graph(int n, double p, bool directed = false){
	std::vector < std::vector<int> > edges;
	std::vector <int> vertex(n);
	for(int i = 0; i < n; ++i) vertex[i] = i;
	if(directed) edges = permutations(vertex, 2);
	else edges = combinations(vertex, 2);
	graph res(n);
	if(p <= 0.0) return res;
	if(p >= 1.0) return complete_graph(n);
	for(int i = 0; i < edges.size(); ++i){
		if(doubleRand() < p){
			res[edges[i][0]].push_back(edges[i][1]);
			if(not directed) res[edges[i][1]].push_back(edges[i][0]);
		}
	}
	return res;
}