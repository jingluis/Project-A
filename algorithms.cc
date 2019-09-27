#include "algorithms.hh"



void i_permutations(const std::vector <int>& iterable, int r, std::vector <std::vector <int> >& res, std::vector <int>& partial_res, std::vector <bool>& visited){
	if(r == 0){
		res.push_back(partial_res);
		return;
	}
	for(int i = 0; i < iterable.size(); ++i){
		if(not visited[i]){
			visited[i] = true;
			partial_res.push_back(iterable[i]);
			i_permutations(iterable, r-1, res, partial_res, visited);
			partial_res.pop_back();
			visited[i] = false;
		}	
	} 
}

std::vector <std::vector <int> > permutations(const std::vector <int>& iterable, int r){
	r = (r == 0) ? iterable.size() : r;
	std::vector <std::vector <int> > res;
	std::vector <int> partial_res;
	std::vector <bool> visited(iterable.size(), false);
	i_permutations(iterable, r, res, partial_res, visited);
	return res;
}

void i_combinations(const std::vector <int>& iterable, int r, std::vector <std::vector <int> >& res, std::vector <int>& partial_res, int index){
	if(r == 0){
		res.push_back(partial_res);
		return;
	}
	for(int i = index + 1; i < iterable.size(); ++i){
		partial_res.push_back(iterable[i]);
		i_combinations(iterable, r-1, res, partial_res, i);
		partial_res.pop_back();	
	} 
}

std::vector <std::vector <int> > combinations(const std::vector <int>& iterable, int r){
	r = (r == 0) ? iterable.size() : r;
	std::vector <std::vector <int> > res;
	std::vector <int> partial_res;
	i_combinations(iterable, r, res, partial_res, -1);
	return res;
}

void i_combinations_map(const std::map <int, std::vector<double> >& iterable, int r, std::vector < std::vector<std::pair<int, std::vector<double> > > > & res, std::vector<std::pair<int, std::vector<double> > > partial_res, int index){
	if(r == 0){
		res.push_back(partial_res);
		return;
	}
	int i = 0;
	for(auto w : iterable){
		if(i >= index + 1){
			partial_res.push_back(std::make_pair(w.first, w.second));
			i_combinations_map(iterable, r-1, res, partial_res, i);
			partial_res.pop_back();
		}
		++i;
	}
}

std::vector < std::vector<std::pair<int, std::vector<double> > > > combinations_map(const std::map <int, std::vector<double> >& iterable, int r){
	r = (r == 0) ? iterable.size() : r;
	std::vector < std::vector<std::pair<int, std::vector<double> > > > res;
	std::vector<std::pair<int, std::vector<double> > > partial_res;
	i_combinations_map(iterable, r, res, partial_res, -1);
	return res;
}