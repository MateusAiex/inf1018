#include <stdio.h>

int is_little(){
	int i = 0x01020304;
	unsigned char *p = (unsigned char*) &i;
	if (*p == (i&0xFF))
	{
		return 1;
	}
	else{
		return 0;
	}
}

int main(void){
	int i = is_little();
	if (i)
	{
		printf("little endian\n");
	}
	else{
		printf("big endia\n");
	}
	return 0;
}