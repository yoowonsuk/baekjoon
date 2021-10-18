#include <stdio.h>
#include <math.h>

int main(void)
{
	long long min, max;
	int count = 0;
	int i, j;
	long long temp;

	scanf("%lld %lld", &min, &max);
	temp = (long long)sqrt((double)max);
	for(i=min; i<=max; i++)
		for(j=2; j<= temp; j++)
		{
			if(i%(j*j) == 0)
			{
				count++;
				break;
			}
			else if(i / (j*j) == 0)
				break;
		}


	printf("%d", max-min+1+count);
	return 0;
}



