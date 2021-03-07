#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>

bool Greedy = false;
using namespace std;
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
  unordered_map<int, pair<int, string>> dict;		// {index: [number, string]}
  const unsigned int N; 							// size of array
  vector<unsigned int> a;							// array
  vector<unordered_map<int, bool>> f;				// feasible matrix
  unordered_map<int, bool> dummy;					// dummy map
 public:
  Ssum(vector<pair<int, string>> &parsed) : N(parsed.size()) {
	int n = 0;
	for (auto &p: parsed) {
	  a.push_back(p.first);
	  f.push_back(dummy);
	  dict[n++] = p;
	}
  }
  unsigned long num_table_entries() {
	unsigned int total = 0;
	for (int i = 0; i < this->f.size(); i++) {
	  total += f[i].size();
	}
	return total;
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
		f[n - 1][tgt] = feasible(n - 1, tgt - a[n - 1]) or feasible(n - 1, tgt);
	  else
		f[n - 1][tgt] = feasible(n - 1, tgt) or feasible(n - 1, tgt - a[n - 1]);
	}
	return f[n - 1][tgt];
  }
  int num_solutions() {
	// TODO
	if ((n == 0 and T > 0) or T < 0)
	  return 0;
	if (T == 0)
	  return 1;
	return num_solutions(n - 1, T) + num_solutions(n - 1, T - a[n - 1]);
	return 0;
  }
  int smallest_subset() {
	int smallest_subset(int n, int T) {
	// TODO
    int element_size = n.size();
    int small_length = numeric_limits<int>::max();
    for (int i = 0; i < element_size && small_length > 1; i++) {
      int sum = 0;
      for (int j = i; j < t; j++) {
        sum += n[j]
        if (sum >= T) {
          small_length = min(small_length, j - i + 1);
          break;
        }
      }
      }
        return small_length == numeric_limits<int>::max() ? small_length;
    }
	  
  int num_smallest_subsets() {
	// TODO
	return 0;
  }
  int lex_first_solution() {
	// TODO
	return 0;
  }

};

int main(int argc, char *argv[]) {
  unsigned int target = stoi(argv[1]);
//  unordered_map<int, pair<int, string>> parsed;
  vector<pair<int, string>> parsed;
  int num;
  string str;
  while (cin >> num && cin >> str)
	parsed.emplace_back(num, str);
  Ssum ssum(parsed);
  if (ssum.feasible(parsed.size(), target)) {
	std::cout << "Number of distinct solutions:\t\t\t\t" << ssum.num_solutions() << endl;
	std::cout << "Size of smallest satisfying subset:\t\t\t" << ssum.smallest_subset() << endl;
	std::cout << "Number of min-size satisfying subsets:\t\t" << ssum.num_smallest_subsets() << endl;
	std::cout << "Lexicographically first min-sized solution:\t" << ssum.lex_first_solution() << endl;
  } else {
	std::cout << "INFEASIBLE";
  }
}

