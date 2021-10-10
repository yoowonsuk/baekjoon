#include <stdio.h>

int main(void)
{
	int i, j;
	int a, b;
	int T;
	int temp;
	scanf("%d", &T);

	for(i=0; i<T; i++)
	{
		scanf("%d %d", &a, &b);
		temp = a;
		for(j=0; j<b-1; j++)
			if(!temp)
				break;
			else
				temp = temp * a % 10;

		if(!(temp%10))
			printf("%d\n", 10);
		else
			printf("%d\n", temp % 10);
	}

	return 0;
}
