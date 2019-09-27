#include <iostream>
#include <vector>
#include "random_graphs.hh"
using namespace std;
using graph = std::vector <std::vector <int> >;


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

void GNP_test () {
	int numVert;
	double p;
	bool directed;
	cin >> numVert >> p >> directed;
	graph g_test;
	g_test = erdos_renyi_random_graph(numVert, p, directed);
	cout << "\n\nAdjacency Matrix\n\n";
	for (vector<int> v : g_test) {
		for (int i : v) {
			cout << i << " ";
		}
		cout << endl;
	}
	cout << "\n\nConnected Component\n\n";
	graph component;
	connex_components(g_test, component);
	for (vector<int> v : component) {
		for (int i : v) cout << i << " ";
		cout << endl;
	}
	cout << endl;
}

void RGG_test () {
	int numVert;
	double radius;
	cin >> numVert >> radius;
	graph g_test;
	g_test = random_geometric_graph(numVert, radius);
	cout << "\n\nAdjacency Matrix\n\n";
	for (vector<int> v : g_test) {
		for (int i : v) {
			cout << i << " ";
		}
		cout << endl;
	}
	cout << "\n\nConnected Component\n\n";
	graph component;
	connex_components(g_test, component);
	for (vector<int> v : component) {
		for (int i : v) cout << i << " ";
		cout << endl;
	}
	cout << endl;
}

int main () {
	while (true) {
		GNP_test();
	}
}
