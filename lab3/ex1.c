#include <stdio.h>

int main(void){
	unsigned int x = 0x87654321;
  	unsigned int y, z;

	y = x & 0xff;
	z = x | 0xff000000;

	printf("%08x %08x\n", y, z);

	return 0;
}