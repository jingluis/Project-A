#include <iostream>
#include <vector>
#include "algorithms.hh"

using graph = std::vector < std::vector <int> >;

graph complete_graph(int n);

graph erdos_renyi_random_graph(int n, double p, bool directed = false);
