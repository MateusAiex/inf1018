#include <stdio.h>

unsigned char switch_byte(unsigned char x){
	return (x << 4) | (x >> 4);
}

unsigned char rotate_left(unsigned char x, int n){
	return (x << n) | (x >> (8 - n));
}

int main(void){
	unsigned char x = 0xab;
	printf("%x\n", switch_byte(x));
	x = 0x61;
	printf("%x\n", rotate_left(x, 1));
	printf("%x\n", rotate_left(x, 2));
	printf("%x\n", rotate_left(x, 7));
	return 0;
}