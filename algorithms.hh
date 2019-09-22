#include <iostream>
#include <vector>
#include <cstdlib>
#include <map>

double doubleRand();


void i_permutations(const std::vector <int>& iterable, int r, std::vector <std::vector <int> >& res, std::vector <int>& partial_res, std::vector <bool>& visited);

std::vector <std::vector <int> > permutations(const std::vector <int>& iterable, int r = 0);

void i_combinations(const std::vector <int>& iterable, int r, std::vector <std::vector <int> >& res, std::vector <int>& partial_res, int index);

std::vector <std::vector <int> > combinations(const std::vector <int>& iterable, int r = 0);

std::vector < std::vector<std::pair<int, std::vector<double> > > > combinations_map(const std::map <int, std::vector<double> >& iterable, int r = 0);
void i_combinations_map(const std::map <int, std::vector<double> >& iterable, std::vector < std::vector<std::pair<int, std::vector<double> > > > & res, int r, std::vector<std::pair<int, std::vector<double> > > partial_res, int index);