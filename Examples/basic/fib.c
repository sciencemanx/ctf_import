#include <stdio.h>

int fib(int n) {
	int a,b,tmp;

	a = 0;
	b = 1;

	for (; n > 0; n--) {
		tmp = b;
		b = a + b;
		a = tmp;
	}

	return a;
}

int main() {
	printf("nothing to see here!\n");
	return 0;
}