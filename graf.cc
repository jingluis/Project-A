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
	string res;
	cout << "Introduce number of vertexs: ";
	cin >> numVert;
	cout << "Introduce the probability: ";
	cin >> p;
	cout << "Introduce if you want the graph be directed: (yes/no): ";
	cin >> res;
	if(res == "yes" or res == "y") directed = true;
	else directed = false;
	graph g_test;
	g_test = erdos_renyi_random_graph(numVert, p, directed);
	cout << "\n\nAdjacency List\n\n";
	int i = 0;
	for (vector<int> v : g_test) {
		cout << "Vertex " << i++ << ": ";
		for (int i : v) {
			cout << i << " ";
		}
		cout << endl;
	}
	cout << "\n\nConnected Components\n\n";
	graph component;
	connex_components(g_test, component);
	i = 0; 
	for (vector<int> v : component) {
		cout << "Connected Component " << i++ << ": ";
		for (int i : v) cout << i << " ";
		cout << endl;
	}
	cout << "Number of connected components: " << component.size() << endl;
	cout << endl;
}

/* Runs a geometric random graph test outputting the Adjacency List of graph G = (V,E) and its connected component */
void RGG_test () {
	int numVert;
	double radius;
	cout << "Introduce number of vertexs: ";
	cin >> numVert;
	cout << "Introduce the radius: ";
	cin >> radius;
	graph g_test;
	g_test = random_geometric_graph(numVert, radius);
	cout << "\n\nAdjacency List\n\n";
	int i = 0;
	for (vector<int> v : g_test) {
		cout << "Vertex " << i++ << ": ";
		for (int i : v) {
			cout << i << " ";
		}
		cout << endl;
	}
	cout << "\n\nConnected Components\n\n";
	graph component;
	connex_components(g_test, component);
	i = 0; 
	for (vector<int> v : component) {
		cout << "Connected Component " << i++ << ": ";
		for (int i : v) cout << i << " ";
		cout << endl;
	}
	cout << "Number of connected components: " << component.size() << endl;
	cout << endl;
}

/*
	Returns true if the probability of a G = (V,E) with numVert vertex being connected with probability p is 1 with 100 tests, false otherwise
	Pre: numVert > 0, 0.0 <= p <= 1.0, directed indicates whether the graph will be directed or not, ermon indicates if the graph is gnp or rgg,
			 res stores the probability, and connex_c stores the waiting number of connected component.
*/
bool Statistic_test(int numVert, float p, bool directed, bool ermon, float& res, float& connect_c) {
	int connexed, connexed_components;
	connexed = connexed_components = 0;
	for (int i = 0; i < 1000; ++i) {
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
	res = float(connexed)/1000.0;
	connect_c = float(connexed_components)/1000.0;
	if(res >= 1) return true;
	return false;
}

/*
	Returns true if the probability of a G = (V,E) with numVert vertex and numEdge edge being connected with probability p is 1 with 100 tests, false otherwise
	Pre: numVert > 0, 0 <= numEdge <= numVert*(numVert-1)/2, 0.0 <= p <= 1.0, directed indicates whether the graph will be directed or not, ermon indicates if the graph is gnp or rgg,
			 res stores the probability.
*/
bool Statistic_Edges_Connexed(int numVert, int numEdge, float p, bool directed, bool ermon, float& res) {
	int connexed;
	connexed = 0;
	for (int i = 0; i < 100; ++i) {
		graph g_test;
		if (ermon) g_test = erdos_renyi_random_graph_with_EdgeNumber_fixed(numVert, p, numEdge, directed);
		else g_test = random_geometric_graph(numVert, p);
		vector<int> partial_res;
		vector<bool> visited(numVert, false);
		depth_first_search(0,visited, partial_res, g_test);
		connexed += numVert == partial_res.size();
	}
	res = float(connexed)/100.0;
	if (res == 1) return true;
	return false;
}

/* 
	 stores the result in files of the statistic tests for graphs with 10 - 100 vertexs, increasing 10 vertexs per loop
	 ermon indicates if the graph is gnp or rgg
	 opt indicates which result we wanna obtain:
	 - 1: probability to be connected 
	 - 2: waiting number of CC 
*/	 

void get_statistic_data_file(bool ermon, int opt){
	for(int n = 10; n <= 100; n += 10){
		bool b = false;
		string file =  to_string(n) + ".txt";
		ofstream output(file);
		for(float i = 0.001f; i <= 1.0f; i += 0.001f){
			output << i << " ";
			float res;
			float connect_c;
			if(not b){
				b = Statistic_test(n, i, false, ermon,res, connect_c);
				if(opt == 1) output << res;
				else output << connect_c;
			}
			else output << 1;
			output << endl;
		}
	}
}

/* 
	 stores the result in files of the statistic tests for graphs with 10 - 100 vertexs, increasing 10 vertexs per loop
	 ermon indicates if the graph is gnp or rgg
	 Returns the relation beetwen the size of the random generated graph and it's conectivity
*/


void get_statistic_Edges_Connexed_file(bool ermon) {
	for (int i = 10; i <= 100; i += 10) {
		int max_Edge_number = (i*(i-1))/2;
		for (float j = 0.1f; j < 1.1f; j += 0.1f) {
			bool b = false;
			string file =  to_string(i) + " with p = " + to_string(j) + ".txt";
			ofstream output(file);
			for (int k = 0; k <= max_Edge_number; ++k) {
				output << k << " ";
				float res;
				if (not b) {
					b = Statistic_Edges_Connexed(i, k, j, false, ermon, res);
					output << res;
				}
				else output << 1;
				output << endl;
			}
		}
	}
}




int main () {
	srand(time(0));
	int opt;
	while(true){
		cout << "Please choose which activity you want to perform:" << endl;
		cout << "1) run a Binomial Random graph test" << endl;
		cout << "2) run a Geometric Random graph test" << endl;
		cout << "3) run a statistic test" << endl;
		cin >> opt;
		switch(opt){
			case 1:
				GNP_test();
				cout << "Test run correctly" << endl;
				break;
			case 2:
				RGG_test();
				cout << "Test run correctly" << endl;
				break;
			case 3:
				cout << "Please choose which kind of random graph you want to run the test" << endl;
				cout << "1) Geometric Random Graph" << endl;
				cout << "2) Binomial Random Graph" << endl;
				int ermon;
				cin >> ermon;
				bool b = (ermon == 1)? false:true;
				cout << "Please choose which kind of statistic test you want to obtain" << endl;
				cout << "1) probability of the graph being connected" << endl;
				cout << "2) number of waiting connected components of a graph" << endl;
				int i;
				cin >> i;
				get_statistic_data_file(b, i);
				cout << "Statistic data collected correctly" << endl;
				break;
		}
		cout << endl;
	}
}
