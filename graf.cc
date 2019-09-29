#include "random_graphs.hh"


int test_value[] = {10,50,100,250,500,1000};


void depth_first_search(int i, vector<bool>& visited, vector<int>& partial_res, const graph& g, int& cc_size){
	if(not visited[i]){
		visited[i] = true;
		partial_res.push_back(i);
		for(int w : g[i]){
			if(not visited[w]){
				++cc_size;
				depth_first_search(w,visited,partial_res,g,cc_size);
			}
		}
	}
	return;
}

/* 
	Return a list of each connex component of a graph g and the biggest CC size
	g is a G = (V,E) with n vertex and m edges represented by an adjacency list 
 	Computation cost: O(|V|+|E|)
*/
int max_connex_components(const graph& g, vector < vector <int> >& res){
	int V = g.size();
	int max_cc_size = -1;
	vector <bool> visited(V, false);
	for(int i = 0; i < V; ++i){	
		if(not visited[i]){
			int cc_size = 1;
			vector <int> partial_res;
			depth_first_search(i,visited,partial_res,g, cc_size);
			res.push_back(partial_res);
			max_cc_size = max(max_cc_size,cc_size);
		}
	}
	return max_cc_size;
}

/* Runs a binomial random graph test outputting the Adjacency List of graph G = (V,E) and its connected component */
void GNP_test () {
	int numVert;
	double p;
	string res;
	cout << "Introduce number of vertexs: ";
	cin >> numVert;
	cout << "Introduce the probability: ";
	cin >> p;
	graph g_test;
	g_test = erdos_renyi_random_graph(numVert, p);
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
	max_connex_components(g_test, component);
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
	max_connex_components(g_test, component);
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
	Returns true if the probability of a G = (V,E) with numVert vertex and numEdge edge being connected with probability p is 1 with 100 tests, false otherwise
	Pre: numVert > 0, 0 <= numEdge <= numVert*(numVert-1)/2, 0.0 <= p <= 1.0, ermon indicates if the graph is gnp or rgg,
			 res stores the probability.
*/
bool Statistic_Edges_Connexed(int numVert, int numEdge, float p, bool ermon, float& res) {
	int connexed;
	connexed = 0;
	for (int i = 0; i < 100; ++i) {
		graph g_test;
		if (ermon) g_test = erdos_renyi_random_graph(numVert, p, true, numEdge);
		else g_test = random_geometric_graph(numVert, p, 2, 2.0, true, numEdge);
		vector<int> partial_res;
		vector<bool> visited(numVert, false);
		int aux = 0;
		depth_first_search(0,visited, partial_res, g_test, aux);
		connexed += numVert == partial_res.size();
	}

	res = float(connexed)/100.0;
	if (res == 1) return true;
	return false;
}

/*
	Returns true if the probability of a G = (V,E) with numVert vertex being connected with probability p is 1 with 100 tests, false otherwise
	Pre: numVert > 0, 0.0 <= p <= 1.0,  ermon indicates if the graph is gnp or rgg,
			 res stores the probability, and connex_c stores the waiting number of connected component.
*/
bool Statistic_test(int numVert, float p, bool ermon, float& res, float& connect_c, float & max_cc) {
	int connexed, connexed_components, max_cc_s;
	connexed = connexed_components = 0;
	for (int i = 0; i < 1000; ++i) {
		graph g_test;
		if (ermon) g_test = erdos_renyi_random_graph(numVert, p);
		else g_test = random_geometric_graph(numVert, p);
		graph component;
		max_cc_s += max_connex_components(g_test, component);
		connexed_components += component.size();
		connexed += (component.size() == 1);
	}
	/*cout << "El graf aleatori generat amb " << numVert << " vertexs i amb una p = " << p << " te en mitjana:\n";
	cout <<	"possibilitat de ser conex = " << float(connexed)/100.0 << "\ncomponents conexos esperat = " << float(connexed_components)/100.0 << "\n\n";*/
	res = float(connexed)/1000.0;
	connect_c = float(connexed_components)/1000.0;
	max_cc = float(max_cc_s)/1000.0;
	if(res >= 1) return true;
	return false;
}

/* 
	 stores the result in files of the statistic tests for graphs with c(10,50,100,250,500,1000) vertexs, ermon indicates if the graph is gnp or rgg
	 opt indicates which result we wanna obtain:
	 - 1: probability to be connected 
	 - 2: waiting number of CC 
*/	 

void get_statistic_data_file(bool ermon, int opt){
	for(int n = 0; n <= 5; n += 1){
		bool b = false;
		string file = "";
		if(ermon) file += "gnp_";
		else file += "rgg_";
		if(opt == 1) file += "opt1_";
		else if (opt == 2) file += "opt2_";
		else file += "opt4_";
		file +=  (to_string(n) + ".txt");
		ofstream output(file);
		for(float i = (opt == 2)? 0.001f:0.000f; i <= 1.0f; i += 0.001f){
			output << i << " ";
			float res;
			float connect_c;
			float max_cc;
			if(not b){
				b = Statistic_test(test_value[n], i, ermon,res, connect_c,max_cc);
				if(opt == 1) output << res;
				else if(opt == 2) output << connect_c;
				else output << max_cc;
			}
			else {
				if(opt != 4) output << 1;
				else output << test_value[n];
			}
			output << endl;
		}
	}
}

/* 
	 stores the result in files of the statistic tests for graphs with c(10,50,100,250,500,1000)vertexs, ermon indicates if the graph is gnp or rgg
	 Returns the relation beetwen the size of the random generated graph and it's conectivity
*/


void get_statistic_Edges_Connexed_file(bool ermon) {
	
	for (int i = 0; i <= 5; i += 1) {
		int max_Edge_number = (test_value[i]*(test_value[i]-1))/2;
		for (float j = 0.0f; j < 1.1f; j += 0.1f) {
			bool b = false;
			string file =  to_string(test_value[i]) + " with p = " + to_string(j) + ".txt";
			ofstream output(file);
			for (int k = 0; k <= max_Edge_number; ++k) {
				output << k << " ";
				float res;
				if (not b) {
					b = Statistic_Edges_Connexed(test_value[i], k, j, ermon, res);
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
				cout << "3) relationship beetwen number of edges and connectivity" << endl;
				cout << "4) waiting maximum connected component size" << endl;
				int i;
				cin >> i;
				if(i == 3) get_statistic_Edges_Connexed_file(b);
				else get_statistic_data_file(b, i);
				cout << "Statistic data collected correctly" << endl;
				break;
		}
		cout << endl;
	}
}
