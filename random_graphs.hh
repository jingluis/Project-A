#include "algorithms.hh"



using graph = vector < vector <int> >;

graph complete_graph(int n);

graph erdos_renyi_random_graph(int n, double p, bool directed = false);

void slow_edges(graph& G,const map <int, vector<double>>& pos, double radius, double p, int dim);

graph random_geometric_graph(int n, double radius, int dim = 2, double p = 2.0);
