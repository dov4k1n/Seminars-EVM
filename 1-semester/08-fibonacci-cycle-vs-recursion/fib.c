#include <stdio.h>
#include <stdlib.h>

int fib(int n, int *clock) {
	(*clock)++;

	if (n <= 0) return -1;
	if (n == 1 || n == 2) return 1;

	return fib(n-1, clock) + fib(n - 2, clock);
}

int main() {
	int n = 0, i = 2, f1 = 1, f2 = 1, f3, clock = 0, clock2 = 0;

	printf("enter number\n");
	scanf("%d", &n);

	if (n <= 0) {
		printf("wrong format\n");
		return -1;
	}

	if (n == 1 || n == 2) {
		printf("%dth fibonacci number by cycles ~ 1\n", n);
		printf("clock ~ 1");
		return 0;
	}

	while (i < n) {
		clock2++;
		i += 1;
		f3 = f2 + f1;
		f1 = f2;
		f2 = f3;
	}

	printf("%dth fibonacci number by cycles ~ %d\n", n, f3);
	printf("clock ~ %d\n", clock2);

	if (n > 0) {
		printf("%dth fibonacci number by recursion ~ %d\n", n, fib(n, &clock);
		printf("clock ~ %d\n", clock);
	}

	return 0;
}
