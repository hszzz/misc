#include <stdio.h>

extern int asm_func(int, int, int);

int c_func(int a, int b)
{
	printf("call c_add(%d, %d)\n", a, b);
	return a + b;
}

int main()
{
	printf("call main\n");

	int a = asm_func(1, 2, 3);

	printf("%d\n", a);
	return 0;
}

