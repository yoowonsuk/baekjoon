#include <stdio.h>
#include <math.h>

int main(void)
{
	int min, max;
	int count = 0;
	double temp;
	int i;

	scanf("%d %d", &min, &max);

	for(i=min; i<=max; i++)
	{
		temp = sqrt(i);
		if(floor(temp) != temp)
			count++;
	}

	printf("%d", count);
	return 0;
}



