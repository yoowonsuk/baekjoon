#include <stdio.h>
#include <string.h>

int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};

int arr[50][50];

int M, N, K;
int count;

int isBound(int x, int y)
{
	return x >= 0 && x < M && y >= 0 && y < N;
}

void search(int x, int y)
{
	int i, j;
    
    arr[x][y] = 0;
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			if( !(isBound(x+dx[i], y+dy[i])) )
				continue;
			else
				if(arr[x+dx[i]][y+dy[i]])
					search(x+dx[i], y+dy[i]);
				
}

void sol()
{
	int i, j;

	for(i=0; i<M; i++)
		for(j=0; j<N; j++)
			if(arr[i][j])
			{
				count++;
				search(i, j);
			}
	printf("%d\n", count);
	return;
}



int main(void)
{
	int T, i, j;
	int x, y;

	scanf("%d", &T);
	for(i=0; i<T; i++)
	{
		scanf("%d %d %d", &M, &N, &K);
		for(j=0; j<K; j++)
		{
			scanf("%d %d", &x, &y);
			arr[x][y] = 1;
		}
		count = 0;
		sol();
		memset(arr, 0, sizeof(arr));
	}
	return 0;
}
