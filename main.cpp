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
  unordered_map<int, pair<int, string>> dict;        // {index: [number, string]}
  const unsigned int N;                            // size of array
  vector<int> a;                            // array
  vector<unordered_map<int, bool>> f;                // feasible matrix
  unordered_map<int, bool> dummy;                    // dummy map
//  unordered_map<int, vector<int>> solutions;        // {target: ints that add to that target}
 public:
  Ssum(vector<pair<int, string>> &parsed) : N(parsed.size()) {
	int n = 0;
	for (auto &p: parsed) {
	  a.push_back(p.first);
	  f.push_back(dummy);
	  dict[n++] = p;
	}
//	solutions.emplace(0, NULL);
  }
  // utility function to count up number of table entries post-mortem
  unsigned long num_table_entries() {
	unsigned int total = 0;
	for (int i = 0; i < this->f.size(); i++) {
	  total += f[i].size();
	}
	return total;
  }
  // recursive/memoized implementation of standard dynamic programming algorithm
  // n indicates the size of the candidate set which is in a[0...n-1]
  bool feasible(int n, int T) {
	if ((n <= 0 and T > 0) or T < 0)
	  return false;
	if (T == 0) {
	  return true;
	}
	if (f[n - 1].count(T) == 1) { // known answer
	  return f[n - 1][T];
	} else {
	  f[n - 1][T] = feasible(n - 1, T) or feasible(n - 1, T - a[n - 1]);
//	  bool exclude_case = feasible(n - 1, T);
//	  bool include_case = feasible(n - 1, T - a[n - 1]);
	}
	return f[n - 1][T];
  }
  // The number of distinct subsets that yield a sum of T (of any size)
  int num_solutions(int n, int T) {
	if ((n == 0 and T > 0) or T < 0)
	  return 0;
	if (T == 0)
	  return 1;
	if (n == -1)
	  return 0;
	int solutions = 0;
//	for (int i = 0; i <= n; ++i) {
	for (int i = n; i >= 0; i--) {
	  cout << i;
	  if (feasible(i - 1, T - a[i])) {
		cout << " is feasible with T=" << T << endl;
		solutions += this->num_solutions(i - 1, T - a[i]);
	  } else {
	    cout << " is not feasible with T=" << T << endl;
		cout << "";
	  }

	}
	cout << endl;
	return solutions;
//	for (int i = n; i >= 0; --i) {
//	for (int i = 0; i < n; i++) {
//	  if (feasible(i-1, T - a[i]))
//		solutions += num_solutions(i - 1, T - a[i]);
//	}
//	return solutions;
//
//	for (int i = 1; i <= n; i++) {
//	  if (f[i - 1][T - a[i - 1]])
//		solution += num_solutions(i, T - a[i - 1]);
//	}
//	return solution;
//	return num_solutions(n - 1, T) + num_solutions(n - 1, T - a[n - 1]);

//	for (int i = 1; i <= n; i++) {
//	  if (f[n - 1][T])
//		solutions += num_solutions(n - 1, T);
//	  if (f[n - 1][T - a[n - 1]])
//		solutions += num_solutions(n - 1, T - a[n - 1]);
//	}
//	return solutions;


  }
  // The size of the smallest subset yielding T
  int smallest_subset(int n, int T) {
	// TODO
	return 0;
  }
  // The number of distinct subsets yielding sum T and having minimum size from (2)
  int num_smallest_subsets(int n, int T) {
	// TODO
	return 0;
  }
  // Reports the lexicographically first minimum-size subset which yields the sum of T
  // by listing its members in increasing order of the elements indices
  // if there is a solution
  int lex_first_solution(int n, int T) {
	// TODO
	return 0;
  }

};

int main(int argc, char *argv[]) {
  int target = stoi(argv[1]);
//  unordered_map<int, pair<int, string>> parsed;
  vector<pair<int, string>> parsed;
  int num;
  string str;
  while (cin >> num && cin >> str)
	parsed.emplace_back(num, str);
  int n = parsed.size() - 1;
  Ssum ssum(parsed);
  if (ssum.feasible(n, target)) {
	std::cout << "Number of distinct solutions:\t\t\t\t" << ssum.num_solutions(n, target) << endl;
	std::cout << "Size of smallest satisfying subset:\t\t\t" << ssum.smallest_subset(n, target) << endl;
	std::cout << "Number of min-size satisfying subsets:\t\t" << ssum.num_smallest_subsets(n, target) << endl;
	std::cout << "Lexicographically first min-sized solution:\t" << ssum.lex_first_solution(n, target) << endl;
  } else {
	std::cout << "INFEASIBLE";
  }
}

