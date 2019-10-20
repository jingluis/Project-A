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

bool is_graph_connexed(const graph& g) {
	int V = g.size();
	vector<bool> visited(V, false);
	vector<int> partial_res;
	int cc_size = 1;
	depth_first_search(0, visited, partial_res, g, cc_size);
	return cc_size == V;
}


bool dfs_articulation_point(int v, int& time, const graph& g, vector<bool>& visited, vector<int>& disTime, vector<int>& low, vector<int>& parent) {
     int children = 0;
     visited[v] = true;
     disTime[v] = low[v] = ++time;
     for (int i = g[v].size(); i < g[v].size(); ++i) {
     	int u = g[v][i];
     	if (!visited[u]) {
     		children++;
     		parent[u] = v;
     		dfs_articulation_point(u, time, g, visited, disTime, low, parent);
     		low[v] = min(disTime[u], disTime[v]);
     		if (parent[v] == -1 and children > 1) return true;
     		if (parent[v] != -1 and low[u] >= disTime[v]) return true;
     	}
     	else if(u != parent[v]) low[v] = min(low[u], disTime[v]);
     }
     return false;
}

/* 
	Given an Graph G=(V, E), tell if there's an articulation point or not
*/

bool has_articulation_point(const graph& g) {
	int time = 0;
	vector<bool> visited(g.size(), false);
	vector<int> disTime(g.size(), 0);
	vector<int> low(g.size(), 0);
	vector<int> parent(g.size(), -1);
	return dfs_articulation_point(0, time, g, visited, disTime, low, parent);
}

void switch_(int& x, int& y) {
	int c = x;
	x = y;
	y = c;
}

void rotate(vector<int>& Path, int rotPos) {
	int size = Path.size();
	int numswitch = (size - rotPos)/2;
	for (int i = 1; i <= numswitch; ++i) {
		switch_(Path[rotPos+i], Path[size-i]);
	}
}

void reverse(vector<int>& Path) {
	int size = Path.size();
	int numswitch = size/2;
	--size;
	for (int i = 0; i < numswitch; ++i) {
		switch_(Path[i], Path[size-i]);
	}
}

int choose_random_unvisited_vertex(vector<int>& adjacency, int pHead) {
	int unvisited = adjacency[adjacency.size()-1];
	if (!unvisited) return pHead;
	int prob = rand()%adjacency[adjacency.size()-1]+1;
	int k = 0;
	for (int i = 0; i < adjacency.size()-1; ++i)
	{
		k += adjacency[i] == 1;
		if(k == prob) {
			return i;
		}
	}
}

int choose_random_visited_vertex(vector<int>& adjacency, int k) {
	int prob = rand()%k+1;
	int aux = 0;
	for (int i = 0; i < adjacency.size()-1; ++i)
	{
		aux += adjacency[i] == 2;
		if(aux == prob) {
			return i;
		}
	}
}

int visited_vertex_num(vector<int>& adjacency) {
	int k = 0;
	for (int i = 0; i < adjacency.size()-1; ++i)
	{
		k += adjacency[i] == 2;
	}
	return k;
}

/* 
	Given an Graph G=(V, E), tell if it's Hamiltonian or not.
	Computation Cost: O(NlogN)
*/

bool is_hamiltonian(graph & adjacency) {
	vector<int> Path;
	Path.push_back(rand()%adjacency.size());
	int visited_num = 1;
	vector<bool> visited(adjacency.size(), false);
	int pHead = Path[Path.size()-1];
	int unused = adjacency[pHead][adjacency.size()];
	visited[pHead] = true;
	int times = 40 * adjacency.size()*log2(adjacency.size());
	while(times) {
		--times;
		int k = visited_vertex_num(adjacency[pHead]);
		int prob = rand()%adjacency.size();
		if (prob == 0) {
			reverse(Path);
		}
		else {
			if (prob <= k and k != 0) {
				int newHead = choose_random_visited_vertex(adjacency[pHead], k);
				int rotPos = 0;
				if (newHead == Path[0] and visited_num == adjacency.size()) {
					return true;
				}
				for (int i = 0; i < Path.size()-1 and Path[i] != newHead; ++i) {
					++rotPos;
				}
				rotate(Path, rotPos);
			}
			else {
				int newHead = choose_random_unvisited_vertex(adjacency[pHead], pHead);
				if (!visited[newHead]) {
					--adjacency[pHead][adjacency.size()];
					--adjacency[newHead][adjacency.size()];
					adjacency[newHead][pHead] = 2;
					adjacency[pHead][newHead] = 2;
					Path.push_back(newHead);
					++visited_num;
					visited[newHead] = true;
					if (newHead == Path[0] and visited_num == adjacency.size()) return true;
				}
				else{
					if (newHead == Path[0] and visited_num == adjacency.size()) return true;
					int rotPos = 0;
					for (int i = 0; i < Path.size()-1 and Path[i] != newHead; ++i) {
						++rotPos;
					}
					rotate(Path, rotPos);
					adjacency[Path[Path.size()-1]][Path[rotPos]] = 2;
					adjacency[Path[rotPos]][Path[Path.size()-1]] = 2;
					--adjacency[Path[Path.size()-1]][adjacency.size()];
					--adjacency[Path[rotPos]][adjacency.size()];
				}
			}
		}
		pHead = Path[Path.size()-1];
		unused = adjacency[pHead][adjacency.size()];
	}
	return false;
}

/* 
	Given an Graph G=(V, E), tell if it's Hamiltonian or not according to Dirac's theorem.
*/

bool has_hamiltonian_cycle_dirac(const graph& g) {
	int num_vertex = g.size() + g.size()%2;
	for (int i = 0; i < g.size(); ++i) {
		if (g[i].size() < num_vertex/2) return false;
	}
	return true;
}

/*
	Given an random graph G = (V, E) tell if it contains an Hamiltonian cycle or not.
*/

bool has_hamiltonian_cycle(const graph& g, graph& adjacency) {
	if (!is_graph_connexed(g)) return false;
	if (has_articulation_point(g)) return false;
	return has_hamiltonian_cycle_dirac(g) or is_hamiltonian(adjacency);
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
	graph adjacency(numVert, vector<int>(numVert+1, 0));
	g_test = erdos_renyi_random_graph(numVert, p, adjacency);
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
	graph adjacency(numVert, vector<int> (numVert+1, 0));
	g_test = random_geometric_graph(numVert, radius, adjacency);
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
		graph adjacency(numVert, vector<int>(numVert+1, 0));
		if (ermon) g_test = erdos_renyi_random_graph(numVert, p, adjacency, true, numEdge);
		else g_test = random_geometric_graph(numVert, p, adjacency, 2, 2.0, true, numEdge);
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
	connexed = connexed_components = max_cc_s = 0 ;
	for (int i = 0; i < 1000; ++i) {
		graph g_test;
		graph adjacency(numVert, vector<int>(numVert+1, 0));
		if (ermon) g_test = erdos_renyi_random_graph(numVert, p, adjacency);
		else g_test = random_geometric_graph(numVert, p, adjacency);
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


bool Statistic_is_Hamiltonian_GNP(int numVert, float r, float& res) {
	int hamiltonian = 0;
	graph g;
	for (int i = 0; i < 1000; ++i) {
		graph g_test;
		graph adjacency(numVert, vector<int> (numVert+1, 0));
		g_test = erdos_renyi_random_graph(numVert, r, adjacency);
		hamiltonian += has_hamiltonian_cycle(g_test, adjacency);
		g = adjacency;
	}
	res = float(hamiltonian)/1000;
	return res == 1;
}

bool Statistic_is_Hamiltonian_RGG(int numVert, float r, float& res) {
	int hamiltonian = 0;
	graph g;
	for (int i = 0; i < 1000; ++i) {
		graph g_test;
		graph adjacency(numVert, vector<int> (numVert+1, 0));
		g_test = random_geometric_graph(numVert, r, adjacency);
		hamiltonian += has_hamiltonian_cycle(g_test, adjacency);
		g = adjacency;
	}
	res = float(hamiltonian)/1000;
	return res == 1;
}

void get_statistic_Hamiltonian_GNP_file() {

	for (int i = 0; i <= 5; i += 1) {
		bool b = false;
		string file = "gnp_opt5_" +to_string(i) + ".txt";
		ofstream output(file);
		for (float j = 0.001f; j < 1.1f; j += 0.001f) {
			float res;
			output << j << " ";
			if (not b) {
				b = Statistic_is_Hamiltonian_GNP(test_value[i], j, res);
				output << res << endl;
 			}
			else output << 1 << endl;
		}
	}
}

void get_statistic_Hamiltonian_RGG_file() {

	for (int i = 0; i <= 5; i += 1) {
		bool b = false;
		string file = "rgg_opt5_" +to_string(i) + ".txt";
		ofstream output(file);
		for (float j = 0.001f; j < 1.1f; j += 0.001f) {
			float res;
			output << j << " ";
			if (not b) {
				b = Statistic_is_Hamiltonian_GNP(test_value[i], j, res);
				output << res << endl;
 			}
			else output << 1 << endl;
		}
	}
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
		int max_Edge_number = test_value[i]*log2(test_value[i]);
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
				cout << "5) possibility of the graph being hamiltonian" << endl;
				int i;
				cin >> i;
				if(i == 3) get_statistic_Edges_Connexed_file(b);
				else if (b and i == 5) get_statistic_Hamiltonian_GNP_file();
				else if (!b and i == 5) get_statistic_Hamiltonian_RGG_file();
				else get_statistic_data_file(b, i);
				cout << "Statistic data collected correctly" << endl;
				break;
		}
		cout << endl;
	}
}
