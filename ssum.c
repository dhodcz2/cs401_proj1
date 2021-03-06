

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int target;
  unsigned int *a;
  int n;
  int **feasible;  // feasible[i][x] = 1 if there is a subset
		   //  of a[0..i] adding up to x; zero otherwise
  int done;        // flag indicating if dp has been run or not
} SS_INSTANCE;

void free_2d_arr(int **m, int r) {
  int i;
  for(i=0; i<r; i++) {
    free(m[i]);
  }
  free(m);
}

int ** alloc_2d_arr(int r, int c) {
  int i;
  int **m = malloc(r*sizeof(int *));

  for(i=0; i<r; i++) {
    m[i] = malloc(c*sizeof(int));
  }
  return m;
}


SS_INSTANCE * 
init_instance(unsigned int a[], int n, unsigned int target) {
SS_INSTANCE *ssi = malloc(sizeof(SS_INSTANCE));

  ssi->target = target;
  ssi->a = a;
  ssi->n = n;
  ssi->feasible = alloc_2d_arr(n, target+1);
  ssi->done = 0;

  return ssi;
}

void free_instance(SS_INSTANCE *ssi) {

  free_2d_arr(ssi->feasible, ssi->n);
  free(ssi);
}

int ssum_run(SS_INSTANCE *ssi) {
  int i, n;
  unsigned int x, tgt, *a;

  // just to save some typing below...
  a = ssi->a;   
  tgt = ssi->target;
  n = ssi->n;

  for(i=0; i<n; i++) {
    ssi->feasible[i][0] = 1;
  }
  for(x=1; x<=tgt; x++) {
    if(a[0] == x) {
      ssi->feasible[0][x] = 1;
    }
    else {
      ssi->feasible[0][x] = 0;
    }
  }
  for(i=1; i<n; i++) {
    for(x=1; x<=tgt; x++) {
      if(ssi->feasible[i-1][x]) {
        ssi->feasible[i][x] = 1;
      }
      else if(x >= a[i] && ssi->feasible[i-1][x-a[i]]){
        ssi->feasible[i][x] = 1;
      }
      else {
        ssi->feasible[i][x] = 0;
      }
    }
  }
  ssi->done = 1;
  return ssi->feasible[n-1][tgt];
}


/**
* usage:  ssum <max-ints-to-read> <target> < <file-of-integers>
*
*/
int main(int argc, char *argv[]) {
  int max_n, n;
  unsigned int target, *a, val;
  SS_INSTANCE *ssi;
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

  ssi = init_instance(a, n, target);
  success = ssum_run(ssi);

  if(success)
    printf("YES!  There is a subset totaling %u\n", target);
  else
    printf("NOPE!  There is no subset totaling %u\n", target);

  free_instance(ssi);
  free(a);

}
