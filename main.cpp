#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>

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
struct element {
  int val;
  string str;
  element(int val, string str) : val(val), str(str) {};
};

class Ssum {
  vector<int> a;                            // array
  vector<unordered_map<int, bool>> f;                // feasible matrix
  unordered_map<int, bool> dummy;                    // dummy map
  vector<element> elements;

  vector<vector<unsigned long long>> distinct;
  vector<vector<unsigned long long>> sum_distinct;
  vector<vector<vector<int>>> min_subsets;
  vector<vector<unsigned long long>> num_min_subsets;
 public:
  int N;                            // size of array
  int T;
  explicit Ssum(const string &T) : T(stoi(T)) {
	int val;
	string str;
	while (cin >> val and cin >> str) {
	  elements.emplace_back(val, str);
	  a.push_back(val);
	  f.push_back(dummy);
	}
	N = elements.size();
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
//  bool feasible(int n, int T) {
  bool feasible(int n, int t) {
	if ((n == 0 and t > 0) or t < 0)
	  return false;
	if (t == 0) {
	  return true;
	}
	if (f[n - 1].count(t) == 1) { // known answer
	  return f[n - 1][t];
	} else {
	  f[n - 1][t] = feasible(n - 1, t) or feasible(n - 1, t - elements[n - 1].val);

	}
	return f[n - 1][t];
  }

  void build() {
	distinct.resize(N);
	sum_distinct.resize(N);
	min_subsets.resize(N);
	num_min_subsets.resize(N);

	// inductive case : number of distinct subsets
	// distinct[i][T] show number of subsets that achieve sum of t, having i-th element as last
	// sum_distinct[i][t] stores sum of all distinct[0...i-1][t] for easier calculations
	// min_subsets[i][T] stores minimial subset that achieves sum t with elements smaller than or equal to i
	// num_min_subsets [i][t] stores number of such minimal subsets

	// Initialize matrices
	for (int i = 0; i < N; i++) {
	  distinct[i].resize(T + 1, 0);
	  sum_distinct[i].resize(T + 1, 0);
	  min_subsets[i].resize(T + 1);
	  num_min_subsets[i].resize(T + 1);
	}

	// Construct base case
	if (elements[0].val <= T) {
	  distinct[0][elements[0].val] = 1;                    // 1 distinct way to order the first element
	  sum_distinct[0][elements[0].val] = 1;                    // 1 total element needed to get to the first element
	  min_subsets[0][elements[0].val].push_back(0);    // the first element is smallest subset to get first element
	  num_min_subsets[0][elements[0].val] = 1;        //  one way to store minimal subset
	}
	for (int i = 1; i < N; i++) {
	  for (int t = 1; t <= T; t++) {
		// Copy min subset from previous level
		min_subsets[i][t] = min_subsets[i - 1][t];
		num_min_subsets[i][t] = num_min_subsets[i - 1][t];
		// Then check it

		if (elements[i].val > t) {
		  // elements[x] is unachievable

		} else if (elements[i].val == t) {
		  // subset contains only one element and achieves sum t
		  distinct[i][t] = 1;
		  sum_distinct[i][t]++;
		  min_subsets[i][t] = vector<int>{i};
		  num_min_subsets[i][t] = 1;

		} else {
		  // subset contains other elements, we know how much from sum[i-1][t-elem[i]]
		  int prev_t = t - elements[i].val;
		  distinct[i][t] = sum_distinct[i - 1][prev_t]; // If there are previously sum many solutions,
		  // the include case will make them all unique.

		  if (min_subsets[i - 1][prev_t].empty()) {
//			 cannot start nonempty sum with empty subset

		  } else if (min_subsets[i][t].empty() or
			  min_subsets[i - 1][prev_t].size() + 1 < min_subsets[i][t].size()) {
			// if previous subset is shorter even when including this one, update current with it
			min_subsets[i][t] = min_subsets[i - 1][prev_t];
			min_subsets[i][t].push_back(i);
			num_min_subsets[i][t] = num_min_subsets[i - 1][prev_t];

		  } else if (min_subsets[i - 1][prev_t].size() + 1 == min_subsets[i][t].size()) {
			auto lex_smaller = [&](vector<int> &first, vector<int> &second) {
			  auto f = first.begin();
			  auto s = second.begin();
			  while (f != first.end() and s != second.end()) {
				if (*(f++) > *(s++)) // could be >=?
				  return false;
			  }
			  return true;
			};
			if (lex_smaller(min_subsets[i - 1][t], min_subsets[i][t]))
			  min_subsets[i][t] = min_subsets[i - 1][t];
			num_min_subsets[i][t]++;
		  }
		}
		// recalculate sum for current step
		sum_distinct[i][t] = sum_distinct[i - 1][t] + distinct[i][t];
	  }
	}
  }

  // The number of distinct subsets that yield a sum of T (of any size)
  unsigned long long get_num_distinct_solutions() {
	return sum_distinct[N - 1][T];
//	return distinct[N-1][T]; // Distinct would only imply that the solution includes elements[N-1]
  }

  unsigned long long get_smallest_subset() {
	return min_subsets[N - 1][T].size();
  }
  // The number of distinct subsets yielding sum T and having minimum size from (2)
  int get_num_smallest_solutions() {
	int count = 0;
	for (int i = 0; i < N; i++)
	  count += num_min_subsets[i][T];
	return count;
  }
  // Reports the lexicographically first minimum-size subset which yields the sum of T
  // by listing its members in increasing order of the elements indices
  // if there is a solution
//  vector<int> get_lex_first_solution() {
//	return subsets[N - 1][T];
//  }
  string get_lex_first_solution() {
	string str = "{";
	vector<int> subset = min_subsets[N - 1][T];
	int i = 0;
	while (i < subset.size() - 1)
	  str += (elements[subset[i++]].str) + ", ";
	if (i == subset.size() - 1)
	  str += (elements[subset[i]].str);
	str.push_back('}');
	return str;
  }

};

int main(int argc, char *argv[]) {
  Ssum ssum(argv[1]);
  if (ssum.feasible(ssum.N, ssum.T)) {
	ssum.build();
	cout << "Target sum of " << ssum.T << " is FEASIBLE" << endl;
	cout << "Number of distinct solutions:\t\t\t" << ssum.get_num_distinct_solutions() << endl;
	cout << "Size of smallest satisfying subset:\t\t" << ssum.get_smallest_subset() << endl;
	cout << "Number of min-size satisfying subsets:\t\t" << ssum.get_num_smallest_solutions() << endl;
	cout << "Lexicographically first min-sized solution:\t" << ssum.get_lex_first_solution() << endl;
  } else {
	cout << "INFEASIBLE";
  }

}

