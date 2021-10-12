#include <stdio.h>

int main(void)
{
	int T;
	int i;
	int x, y;
	int distance;
	double sqr;
	scanf("%d", &T);

	for(i=0; i<T; i++)
	{
		scanf("%d %d", &x, &y);
		distance = y-x;
		sqr = sqrt(y-x);
		if(floor(sqr) == sqr)
			printf("%d\n", (int)sqrt(distance) * 2 - 1);
		else if(floor(sqr) + pow(floor(sqr), 2) >= distance)
			printf("%d\n", (int)floor(sqr) * 2);
		else
			printf("%d\n", (int)floor(sqr) * 2 + 1);
			
	}

	return 0;
}
