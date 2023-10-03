#include <stdio.h>
#define N 10

int f (int x) { return x+2; }

void map2 (int* um, int * outro, int n) {
  int i;
  for (i=0; i<n; i++)
    *(outro+i) = f(*(um+i));
}

int main (void) {
  int i;
  int a[N], b[N];
  for (i=0;i<N;i++)
    a[i] = i;
  map2(a,b,N);
  for (i=0;i<N;i++)
    printf("%d\n",b[i]);
  return 1;
}