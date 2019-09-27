#include <iostream>
#include <vector>
#include "random_graphs.hh"
using namespace std;
using graph = std::vector < std::vector <int> >;


void depth_first_search(int i, std::vector<bool>& visited, std::vector<int>& partial_res, const graph& g){
	if(not visited[i]){
		visited[i] = true;
		partial_res.push_back(i);
		for(int w : g[i]){
			if(not visited[w]) depth_first_search(w,visited,partial_res,g);
		}
	}
	return;
}

// Return a list of each connex component of a graph g
// g is a G = (V,E) with n vertex and m edges represented by an adjacency list 
// Computation cost: O(|V|+|E|)
void connex_components(const graph& g, std::vector < std::vector <int> >& res){
	int V = g.size();
	std::vector <bool> visited(V, false);
	for(int i = 0; i < V; ++i){	
		if(not visited[i]){
			std::vector <int> partial_res;
			depth_first_search(i,visited,partial_res,g);
			res.push_back(partial_res);
		}
	}
	return;
}

int main() {
	int numVert, p;
	bool directed;
	cin >> numVert >> p >> directed;
	graph g_test;
	g_test = erdos_renyi_random_graph(numVert, p, directed);
	vector<int> partial;
	vector<bool> visited (10, false);
	depth_first_search(0, visited, partial, g_test);
	for (int i : partial) {
		cout << i << " ";
	}
	cout << endl;
	graph component;
	connex_components(g_test, component);
	for (vector<int> v : component) {
		for (int i : v) cout << i << " ";
		cout << endl;
	}
}