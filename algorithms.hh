#include "utils.hh"


void i_permutations(const vector <int>& iterable, int r, vector <vector <int> >& res, vector <int>& partial_res, vector <bool>& visited);

vector <vector <int> > permutations(const vector <int>& iterable, int r = 0);

void i_combinations(const vector <int>& iterable, int r, vector <vector <int> >& res, vector <int>& partial_res, int index);

vector <vector <int> > combinations(const vector <int>& iterable, int r = 0);

vector < vector<pair<int, vector<double> > > > combinations_map(const map <int, vector<double> >& iterable, int r = 0);

void i_combinations_map(const map <int, vector<double> >& iterable, vector < vector<pair<int, vector<double> > > > & res, int r, vector<pair<int, vector<double> > > partial_res, int index);