#include <stdio.h>

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
	printf("%p - %02x\n", p1, *p1);
	p1++;
  }
}

int main(void){
  signed char sc = -1;
  unsigned int ui = sc;
  printf("sc = %hhd\n", sc);
  dump(&sc, sizeof(sc));
  printf("ui = %u\n", ui);
  dump(&ui, sizeof(ui));
}