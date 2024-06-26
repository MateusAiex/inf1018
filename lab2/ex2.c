#include <ctype.h>
#include <stdio.h>

int string2num (char *s, int b) {
	int a = 0;
	for (; *s; s++) {
		if ((*s >= '0') && (*s <= '9'))
		{
			a = a * b + (*s - '0');
		}
		else{
			a = a * b + (*s - 'a' + 10);
		}
	}
	return a;
}

int main (void) {
	printf("%d\n", string2num("1a", 16));
	printf("%d\n", string2num("a09b", 16));
	printf("%d\n", string2num("z09b", 36));
	return 0;
}