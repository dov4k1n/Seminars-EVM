#include <stdio.h>
#include <stdlib.h>

unsigned long fib_recursive(int n, unsigned long *op_count);
unsigned long fib_iterative(int n, unsigned long *op_count);

int main()
{
	int n = 0;
	printf("enter number\n");
	while (scanf("%d", &n) != 1 || n <= 0)
	{
		char c = getchar();
		while (c !='\n') c = getchar();
		printf("wrong format, try again\n");
	}

	unsigned long op_count;
	for (int i = 1; i <= n; i++)
	{
		printf("i = %d\n", i);
		op_count = 0;
		printf("iterative ~ %lu, ", fib_iterative(i, &op_count));
		printf("operations ~ %lu\n", op_count);
		op_count = 0;
		printf("recursive ~ %lu, ", fib_recursive(i, &op_count));
		printf("operations ~ %lu\n\n", op_count);
	}

	return 0;
}

unsigned long fib_recursive(int n, unsigned long *op_count)
{
	(*op_count) += 1;
	if (n <= 0) return -1;
	if (n == 1 || n == 2) return 1;
	return fib_recursive(n-1, op_count) + fib_recursive(n-2, op_count);
}

unsigned long fib_iterative(int n, unsigned long *op_count)
{
	(*op_count) += 1;
	if (n <= 0)	return -1;
	if (n == 1 || n == 2) return 1;

	unsigned long result = 0, f1 = 1, f2 = 1;
	(*op_count) = 0;
	for (int i = 0; i < n-2; i++)
	{
		(*op_count) += 5;
		result = f2 + f1;
		f1 = f2;
		f2 = result;
	}
	return result;
}