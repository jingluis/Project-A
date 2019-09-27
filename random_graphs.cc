#include "random_graphs.hh"

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

graph erdos_renyi_random_graph(int n, double p, bool directed){
	std::vector < std::vector<int> > edges;
	std::vector <int> vertex(n);
	for(int i = 0; i < n; ++i) vertex[i] = i;
	if(directed) edges = permutations(vertex, 2);
	else edges = combinations(vertex, 2);
	graph res(n);
	if(p <= 0.0) return res;
	if(p >= 1.0) return complete_graph(n);
	Random_generator rnd;
	for(int i = 0; i < edges.size(); ++i){
		if(rnd.random_double() < p){
			res[edges[i][0]].push_back(edges[i][1]);
			if(not directed) res[edges[i][1]].push_back(edges[i][0]);
		}
	}
	return res;
}

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

graph random_geometric_graph(int n, double radius, int dim, double p){
	int n_name = n;
	graph G(n);
	std::map <int, std::vector <double>> pos;
	Random_generator rnd;
	for(int i = 0; i < n; ++i){
		std::vector <double> pos_aux;
		for(int j = 0; j < dim; ++j) pos_aux.push_back(rnd.random_double());
		pos[i] = pos_aux;
	}
	std::map <int, std::vector<double>>::iterator it;
	for(auto w : pos){
		std::cout << w.first << ": ";
		for(int i = 0; i < w.second.size(); ++i) std::cout << w.second[i] << " ";
		std::cout << std::endl;
	}
	slow_edges(G, pos, radius, p, dim);
	return G;
	
}