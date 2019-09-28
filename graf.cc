#include "random_graphs.hh"





void depth_first_search(int i, vector<bool>& visited, vector<int>& partial_res, const graph& g){
	if(not visited[i]){
		visited[i] = true;
		partial_res.push_back(i);
		for(int w : g[i]){
			if(not visited[w]) depth_first_search(w,visited,partial_res,g);
		}
	}
	return;
}

/* 
	Return a list of each connex component of a graph g
	g is a G = (V,E) with n vertex and m edges represented by an adjacency list 
 	Computation cost: O(|V|+|E|)
*/
void connex_components(const graph& g, vector < vector <int> >& res){
	int V = g.size();
	vector <bool> visited(V, false);
	for(int i = 0; i < V; ++i){	
		if(not visited[i]){
			vector <int> partial_res;
			depth_first_search(i,visited,partial_res,g);
			res.push_back(partial_res);
		}
	}
	return;
}

/* Runs a binomial random graph test outputting the Adjacency List of graph G = (V,E) and its connected component */
void GNP_test () {
	int numVert;
	double p;
	bool directed;
	cin >> numVert >> p >> directed;
	graph g_test;
	g_test = erdos_renyi_random_graph(numVert, p, directed);
	cout << "\n\nAdjacency List\n\n";
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

/* Runs a geometric random graph test outputting the Adjacency List of graph G = (V,E) and its connected component */
void RGG_test () {
	int numVert;
	double radius;
	cin >> numVert >> radius;
	graph g_test;
	g_test = random_geometric_graph(numVert, radius);
	cout << "\n\nAdjacency List\n\n";
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

bool Statistic_test(int numVert, float p, bool directed, bool ermon, float& res, float& connex_c) {
	int connexed, connexed_components;
	connexed = connexed_components = 0;
	for (int i = 0; i < 100; ++i) {
		graph g_test;
		if (ermon) g_test = erdos_renyi_random_graph(numVert, p, directed);
		else g_test = random_geometric_graph(numVert, p);
		graph component;
		connex_components(g_test, component);
		connexed_components += component.size();
		connexed += (component.size() == 1);
	}
	/*cout << "El graf aleatori generat amb " << numVert << " vertexs i amb una p = " << p << " te en mitjana:\n";
	cout <<	"possibilitat de ser conex = " << float(connexed)/100.0 << "\ncomponents conexos esperat = " << float(connexed_components)/100.0 << "\n\n";*/
	res = float(connexed)/100.0;
	connex_c = float(connexed_components)/100.0;
	if(res == 1) return true;
	return false;
}

/* 0: probability to be connected */
/* 1: waiting number of CC */

void get_statistic_data_file(bool ermon, int i){
	for(int n = 10; n <= 100; n += 10){
		bool b = false;
		string file =  to_string(n) + ".txt";
		ofstream output(file);
		for(float i = 0.01f; i <= 1.0f; i += 0.01f){
			output << i << " ";
			float res;
			float connex_c;
			if(not b){
				b = Statistic_test(n, i, false, ermon,res, connex_c);
				if(i == 0) output <<res;
				else output << connex_c;
			}
			else output << 1;
			output << endl;
		}
	}
}



int main () {
	srand(time(0));
	bool ermon;
	cin >> ermon;
	get_statistic_data_file(ermon, 1);
}
