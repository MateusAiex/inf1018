#include <stdio.h>

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

int main (void) {
  int i = 0x01020304;
  dump(&i, sizeof(i));
  printf("\n");
  long l = 10000;
  dump(&l, sizeof(l));
  printf("\n");
  short s = 10000;
  dump(&s, sizeof(s));
  printf("\n");
  char c = 'a';
  dump(&c, sizeof(c));
  printf("\n");
  char p[] = "7509";
  dump(p, sizeof(p));
  printf("\n");
  printf("A , \\n $\n");
  char p2[] = "A,\n$";
  dump(p2, sizeof(p2));
  printf("\n");
  return 0;
}