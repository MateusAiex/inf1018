#include <stdio.h>

int odd_ones(unsigned int x){
	int n1 = 0;
	
	for (int i = 0; i < 32; i++)
	{
		n1 += (x >> i) & 0x1;
	}

	return n1 & 0x1;
}

int main() {
  printf("%x tem numero %s de bits\n",0x01010101,odd_ones(0x01010101) ? "impar":"par");
  printf("%x tem numero %s de bits\n",0x01030101,odd_ones(0x01030101) ? "impar":"par");
  return 0;
}