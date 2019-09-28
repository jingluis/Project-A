#include "algorithms.hh"


/*
Return successive r length permutations of elements in the iterable.
Pre: 	vector iterable has no repeated elements, r should be either 0 or less than iterable.size(),
        visited.size() == iterable.size(),
        visited[i] is true if and only if partial_res contains iterable[i] for all i < iterable.size()
Post:	all vectors of the form {concatenation of partial_res with a r length permutation of {iterable[i] | visited[i] is false}}
        are added to res
*/
void i_permutations(const vector <int>& iterable, int r, vector <vector <int> >& res, vector <int>& partial_res, vector <bool>& visited){
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

/*
Return successive r length permutations of elements in the iterable.
Pre: 	vector iterable has no repeated elements, r should be either 0 or less than iterable.size()
Post:	returns a vector of vector which each line corresponds of the r elements of the permutation, without repeatings.
*/
vector <vector <int> > permutations(const vector <int>& iterable, int r){
	r = (r == 0) ? iterable.size() : r;
	vector <vector <int> > res;
	vector <int> partial_res;
	vector <bool> visited(iterable.size(), false);
	i_permutations(iterable, r, res, partial_res, visited);
	return res;
}

/*
Return r length subsequences of elements from the input iterable.
Pre: 	vector iterable has no repeated elements, r should be either 0 or less than iterable.size()
        partial_res only contains a subset of elements of iterable[0..index]
Post:	all vectors of the form {concatenation of partial_res with a r length subsequence of elements from {iterable[i] | i > index}}
        are added to res
*/
void i_combinations(const vector <int>& iterable, int r, vector <vector <int> >& res, vector <int>& partial_res, int index){
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

/*
Return r length subsequences of elements from the input iterable.
Pre: 	vector iterable has no repeated elements, r should be either 0 or less than iterable.size()
Post:	returns a vector of vector which each line corresponds of the r elements of the combination, without repeatings.
*/
vector <vector <int> > combinations(const vector <int>& iterable, int r){
	r = (r == 0) ? iterable.size() : r;
	vector <vector <int> > res;
	vector <int> partial_res;
	i_combinations(iterable, r, res, partial_res, -1);
	return res;
}

/*
Return r length subsequences of elements from the input iterable.
Pre: 	iterable has no repeated elements, r should be either 0 or less than iterable.size()
        partial_res only contains a subset of the first index+1 elements of iterable, starting from iterable.begin()
Post:	all vectors of the form {concatenation of partial_res with a r length subsequence of elements from {the last iterable.size()-(index+1) elements of iterable}}
        are added to res
*/
void i_combinations_map(const map <int, vector<double> >& iterable, int r, vector < vector<pair<int, vector<double> > > > & res, vector<pair<int, vector<double> > > partial_res, int index){
	if(r == 0){
		res.push_back(partial_res);
		return;
	}
	int i = 0;
	for(auto w : iterable){
		if(i >= index + 1){
			partial_res.push_back(make_pair(w.first, w.second));
			i_combinations_map(iterable, r-1, res, partial_res, i);
			partial_res.pop_back();
		}
		++i;
	}
}

/*
Return r length subsequences of elements from the input iterable.
Pre: 	vector iterable has no repeated elements, r should be either 0 or less than iterable.size()
Post:	returns a vector of vector of pairs of(int, vector) which each line corresponds of the r elements of the combination, without repeatings.
*/
vector < vector<pair<int, vector<double> > > > combinations_map(const map <int, vector<double> >& iterable, int r){
	r = (r == 0) ? iterable.size() : r;
	vector < vector<pair<int, vector<double> > > > res;
	vector<pair<int, vector<double> > > partial_res;
	i_combinations_map(iterable, r, res, partial_res, -1);
	return res;
}
