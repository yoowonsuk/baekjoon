#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int value;
	int i;
	int j;
} Arr;

Arr arr[50];

int compare(const void * a, const void * b)
{
	return ((Arr *)a)->value - ((Arr *)b)->value;
}

int compare1(const void * a, const void * b)
{
	return ((Arr *)a)->i - ((Arr *)b)->i;
}

int main(void)
{
	int i, N;
	scanf("%d", &N);
	for(i=0; i<N; i++)
	{
		scanf("%d", &arr[i].value);
		arr[i].i = i;
	}

	qsort(arr, N, sizeof(arr)/50, compare);

	for(i=0; i<N; i++)
		arr[i].j = i;

	qsort(arr, N, sizeof(arr)/50, compare1);

	for(i=0; i<N; i++)
		printf("%d ", arr[i].j);
	return 0;
}
