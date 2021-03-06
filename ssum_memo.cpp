

#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <vector>

bool Greedy = true;

using std::vector;
using std::unordered_map;

/**
* memoized implementation of standard DP algorithm
*   for subset sum.
*
* Memoization table (named _feasible):
*
*     The table is a vector of unordered maps:
*
*     vector<unordered_map<int, bool>> _feasible;
*
* Interpretation:
*
*     _feasible[i][x] : true if target x sum can be formed
*                          from a subset of a0,a1....ai
*                       false if target x is impossible
*                       <no-entry>:  recursive exploration 
*                           did not explore/need answer to
*                           this subproblem.
*/
 

// utility function to count up number of table entries
//   post-mortem
unsigned long num_table_entries(
    vector<unordered_map<int, bool>> &_feasible){
  unsigned int total=0;
  int i;

  for(i=0; i<_feasible.size(); i++) {
    total += _feasible[i].size();
  }
  return total;
}



// recursive/memoized implementation of standard DP
//   algorithm for subset sum
// NOTE:  n indicates the size of the candidate set
//      which is in a[0..n-1]
bool feasible(vector<unsigned int> &a, int n, int tgt, 
	vector<unordered_map<int, bool>> &_feasible) {

  if((n==0 && tgt > 0) || tgt<0) 
    return false;
  if(tgt==0) {
    // _feasible[n-1][0] = true;  // just to be fair
    return true;
  }
  if(_feasible[n-1].count(tgt)==1) // known answer!
    return _feasible[n-1][tgt];
  else  {
    bool ans;

    if(Greedy) {
         ans = feasible(a, n-1, tgt-a[n-1], _feasible) ||
              feasible(a, n-1, tgt, _feasible); 
    }
    else {
         ans = feasible(a, n-1, tgt, _feasible) ||
		           feasible(a, n-1, tgt-a[n-1], _feasible);
    }
    _feasible[n-1][tgt]=ans;
    return ans;
  }
}

/**
* usage:  ssum_memo <target> < <file-of-integers>
*
*/
int main(int argc, char *argv[]) {
  int max_n, n;
  unsigned int target, *a, val;
  char buf[11];
  int success;
  vector<unsigned int> numbers;
  vector<unordered_map<int, bool>> _feasible;
  unordered_map<int, bool> dummy;


  if(argc < 2) {
    fprintf(stderr, "usage: ./ssum_memo <target> [-z]\n");
    return 0;
  }
  if(sscanf(argv[1], "%u", &target) != 1) {
    fprintf(stderr, "bad argument '%s'\n", argv[2]);
    return 0;
  }
  if(argc > 2)
    Greedy = false;

  n=0;
  while(scanf("%u", &val)==1) {
    scanf("%10s", buf);  // simple program... ignores names...
    numbers.push_back(val);
    _feasible.push_back(dummy);
    n++;
  }


  printf("---- successfully read problem instance ----\n");
  printf("        n:      %i                          \n", n);
  printf("----    target: %i                          \n", target);
  printf("--------------------------------------------\n");

  if(feasible(numbers, n, target, _feasible) )
    printf("YES!  There is a subset totaling %u\n", target);
  else
    printf("NOPE!  There is no subset totaling %u\n", target);

  printf("\nMEMO-TABE SIZE:        %lu\n", 
      num_table_entries(_feasible));
  printf("\nBOTTOM-UP TABLE SIZE:  %d\n", n*target);


}
