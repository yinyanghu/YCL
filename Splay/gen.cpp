#include <cstdio>
#include <ctime>
#include <cstdlib>
#define limit 50000000
#define maxnum 10000
int main()
{
	freopen("in", "w", stdout);
	srand(time(NULL));
	for (int i = 0; i < 200; ++ i)
		printf("0 %d\n", rand() % maxnum);
	for (int i = 100; i < limit; ++ i)
	{
		int x = rand() % 5;
		printf("%d", x);
		if (x >= 0 && x <= 2)
			printf(" %d\n", rand() % maxnum);
		else
			printf("\n");
			
	}
	printf("-1\n");
	return 0;
}
