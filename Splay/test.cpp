#include <cstdio>

int a = 1;
int b = 2;

void f(int * &x1, int * &x2)
{
	x1 = &a;
	x2 = &b;
}

int main()
{

	int *p, *q;
	f(p, q);
	printf("%d %d\n", *p, *q);
}

