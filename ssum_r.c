

#include <stdio.h>
#include <stdlib.h>

 
int feasible(unsigned int a[], int n, int tgt) {

  // known solutions: (int, int) -> true/false
  if(tgt==0) 
    return 1;
  else if(n==0 || tgt<0) 
    return 0;
  else {
    // return feasible(a, n-1, tgt) || feasible(a, n-1, tgt-a[n-1]);
    return feasible(a, n-1, tgt-a[n-1]) || feasible(a, n-1, tgt); 
  }
}

/**
* usage:  ssum <max-ints-to-read> <target> < <file-of-integers>
*
*/
int main(int argc, char *argv[]) {
  int max_n, n;
  unsigned int target, *a, val;
  char buf[11];
  int success;

  if(argc != 3) {
    fprintf(stderr, "two cmd-line args expected: max_N, target\n");
    return 0;
  }
  if(sscanf(argv[1], "%i", &max_n) != 1) {
    fprintf(stderr, "bad argument '%s'\n", argv[1]);
    return 0;
  }
  if(sscanf(argv[2], "%u", &target) != 1) {
    fprintf(stderr, "bad argument '%s'\n", argv[2]);
    return 0;
  }
  a = malloc(max_n * sizeof(unsigned int));

  n=0;
  while(n<max_n && scanf("%u", &val)==1) {
    scanf("%10s", buf);  // simple program... ignores names...
    a[n] = val;
    n++;
  }


  printf("---- successfully read problem instance ----\n");
  printf("        n:      %i                          \n", n);
  printf("----    target: %i                          \n", target);
  printf("--------------------------------------------\n");

  if(feasible(a, n, target) )
    printf("YES!  There is a subset totaling %u\n", target);
  else
    printf("NOPE!  There is no subset totaling %u\n", target);

  free(a);

}
