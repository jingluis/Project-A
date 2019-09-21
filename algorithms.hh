#include <iostream>
#include <vector>
#include <cstdlib>

double doubleRand();


void i_permutations(const std::vector <int>& iterable, int r, std::vector <std::vector <int> >& res, std::vector <int>& partial_res, std::vector <bool>& visited);

std::vector <std::vector <int> > permutations(const std::vector <int>& iterable, int r = 0);

void i_combinations(const std::vector <int>& iterable, int r, std::vector <std::vector <int> >& res, std::vector <int>& partial_res, int index);

std::vector <std::vector <int> > combinations(const std::vector <int>& iterable, int r = 0);