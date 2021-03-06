#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>

bool Greedy = true;
using std::vector;
using std::unordered_map;

/**
 Memoized implementation of standard DP algorithm for subset sum.
 Memoization table (named _feasible):
 	The table is a vector of unordered maps:
 	vector<unordered_map<int, bool>> _feasible;
 Interpretation:
 	_feasible[i][x] :
 		true if target x sum can be formed from a subset of a0,a1....ai
 		<no-entry>: recursive exploration did not explore/ned answer to sub-problem
 */

class Ssum {
  vector<unordered_map<int, bool>> &f;
  vector<unsigned int> &a;
  const unsigned int N;
 public:
//  Ssum(vector<unordered_map<int, bool>> &f, unsigned int N) : f(f), N(N) {}
  Ssum(vector<unordered_map<int, bool>> &f, vector<unsigned int> &a, unsigned int N)
	  : f(f), a(a), N(N) {};
  unsigned long num_table_entries() {
	unsigned int total = 0;
	for (int i = 0; i < this->f.size(); i++) {
	  total += f[i].size();
	}
	return total;
  }
  void print() {
	std::string column_header = "\t";
	for (auto &y: f) {
	  std::string s;
	  std::vector<bool> values;
//	  for (auto &x: y)
//		values.push_back(x);
//	  for (auto &x:)

	}
  }
  bool feasible(int n, unsigned int tgt) {
	if ((n == 0 and tgt > 0) or tgt < 0)
	  return false;
	if (tgt == 0)
	  return true;
	if (f[n - 1].count(tgt) == 1)
	  return f[n - 1][tgt];
	else {
	  if (Greedy)
		f[n - 1][tgt] = feasible( n - 1, tgt - a[n - 1]) or feasible( n - 1, tgt);
	  else
		f[n - 1][tgt] = feasible(n - 1, tgt) or feasible( n - 1, tgt - a[n - 1]);
	}
	return f[n - 1][tgt];
  }
  int num_solutions() {
	// TODO
  }
  int smallest_subset() {
	// TODO
  }
  int num_smallest_subsets() {
	// TODO
  }
  int lex_first_solution() {
	// TODO
  }

};

int main(int argc, char *argv[]) {
  unsigned int target, *a, val;
  char buf[11];
  int success;
  vector<unsigned int> numbers;
  // Dimensions S[1..N][0..T]
  vector<unordered_map<int, bool>> f;
  unordered_map<int, bool> dummy;

  if (argc < 2) {
	fprintf(stderr, "usage: /.ssum_memo <target> [-z]\n");
	return 0;
  } else if (sscanf(argv[1], "%u", &target) != 1) {
	fprintf(stderr, "bad argument '%s',\n", argv[2]);
	return 0;
  } else if (argc > 2) {
	Greedy = false;
  }

  int n = 0;
  while (scanf("%u", &val) == 1) {
	scanf("%10s", buf);
	numbers.push_back(val);
	f.push_back(dummy);
	n++;
  }
  Ssum ssum(f, numbers, n);

  printf("---- successfully read problem instance ----\n");
  printf("        n:      %i                          \n", n);
  printf("----    target: %i                          \n", target);
  printf("--------------------------------------------\n");

//  if (ssum.feasible(numbers, n, target)) {
  if (ssum.feasible( n, target)) {
	std::cout << "Number of distinct solutions:\t\t\t" << ssum.num_solutions();
	std::cout << "Size of smallest satisfying subset:\t\t" << ssum.smallest_subset();
	std::cout << "Number of min-size satisfying subsets:\t" << ssum.num_smallest_subsets();
	std::cout << "Lexicographically first min-sized solution:" << ssum.lex_first_solution();
  } else
	std::cout << "INFEASIBLE";
}
