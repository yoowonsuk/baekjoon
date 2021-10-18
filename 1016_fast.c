#include <stdio.h>
#include <math.h>

#define MAX 1000001
int visit[MAX];

int main(void)
{
	long long min, max;
	int i;
	long long temp;
	int count = 0;

	scanf("%lld %lld", &min, &max);

	for(i=2; i*i<=max; i++)
	{
		temp = min / (i*i);
		if(min % (i*i) != 0)
			temp++;

		while(temp * (i*i) <= max)
		{
			if(visit[temp*i*i - min] == 0)
				count++;
			temp++;
		}
	}
	printf("%d", count);
	return 0;
}
