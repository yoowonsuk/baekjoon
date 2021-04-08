#include <stdio.h>

#define MAX 499

int N;
int sum = 0;
int arr[MAX][MAX] = {0};
int way = -1;
int x, y;

int isBound(int x, int y)
{
	return x >= 0 && x < N && y >= 0 && y < N;
}

void tornado(int which) // which = 1 means y changed, 0 means x changed
{
	int i;
	int rest, origin, temp;
	rest = origin = temp = arr[x][y];
	arr[x][y] = 0;

	if(which) // y changed, go left or right
	{
		temp = origin * 0.05;
		if(isBound(x, y+2*way))
			arr[x][y+2*way] += temp;
		rest -= temp;

		temp = origin * 0.1;
		if(isBound(x+way, y+way))
			arr[x+way][y+way] += temp;
		if(isBound(x-way, y+way))
			arr[x-way][y+way] += temp;
		for(i=0; i<2; i++)
			rest -= temp;

		temp = origin * 0.07;
		if(isBound(x+way, y))
			arr[x+way][y] += temp;
		if(isBound(x-way, y))
			arr[x-way][y] += temp;
		for(i=0; i<2; i++)
			rest -= temp;

		temp = origin * 0.02;
		if(isBound(x+way*2, y)) 
			arr[x+way*2][y] += temp;
		if(isBound(x-2*way, y))
			arr[x-way*2][y] += temp;
		for(i=0; i<2; i++)
			rest -= temp;

		temp = origin * 0.01;
		if(isBound(x-way, y-way))
			arr[x-way][y-way] += temp;
		if(isBound(x+way, y-way))
		arr[x+way][y-way] += temp;
		for(i=0; i<2; i++)
			rest -= temp;

		if(isBound(x, y+way))
		arr[x][y+way] += rest;
	}
	else
	{
		temp = origin * 0.05;
		if(isBound(x+2*way, y))
			arr[x+2*way][y] += temp;
		rest -= temp;

		temp = origin * 0.1;
		if(isBound(x + way, y+way))
			arr[x+way][y+way] += temp;
		if(isBound(x+way, y-way))
			arr[x+way][y-way] += temp;
		for(i=0; i<2; i++)
			rest -= temp;

		temp = origin * 0.07;
		if(isBound(x, y-way))
			arr[x][y-way] += temp;
		if(isBound(x, y+way))
			arr[x][y+way] += temp;
		for(i=0; i<2; i++)
			rest -= temp;

		temp = origin * 0.02;
		if(isBound(x, 2*way+y))
			arr[x][way*2+y] += temp;
		if(isBound(x, y-2*way))
			arr[x][y-2*way] += temp;
		for(i=0; i<2; i++)
			rest -= temp;

		temp = origin * 0.01;
		if(isBound(x-way, y+way))
			arr[x-way][y+way] += temp;
		if(isBound(x-way, y-way))
			arr[x-way][y-way] += temp;
		for(i=0; i<2; i++)
			rest -= temp;

		if(isBound(x+way, y))
			arr[x+way][y] += rest;
	}
}

void solve(void)
{
	//int way = -1;
	int move = 1;
	//int x, y;
	int count = 0;

	x = y = (int)(N/2);

	while(N > move)
	{
		while(count < move)
		{
			count++;
			y += way;
			tornado(1);
		}

		count = 0;
		way *= -1;

		while(count < move)
		{
			count++;
			x += way;
			tornado(0);
		}
		count = 0;
		move++;
	}

	/* last one */
	move--;
	while(count < move)
	{
		count++;
		y += way;
		tornado(1);
	}
}

					

int getOut(void)
{
	int i, j;
	int remain = 0;

	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			remain += arr[i][j];

	return sum - remain;
}

int main(void)
{
	int i, j;

	scanf("%d", &N);

	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
		{
			scanf("%d", &arr[i][j]);
			sum += arr[i][j];
		}

	solve();
	printf("%d", getOut());
	return 0;
}


