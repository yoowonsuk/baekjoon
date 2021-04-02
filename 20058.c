#include <stdio.h>

#define MAX 64
#define NRANGE 6

//#define max(a, b) (((a) > (b)) ? (a) : (b))
//doesn't work in this case due to visited

int max(int x, int y)
{
	return x > y ? x : y;
}

int N, Q;
int A[MAX][MAX], temp[MAX][MAX];
int L[NRANGE];
int visited[MAX][MAX];
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};

int inRange(int x, int y)
{
	return x >= 0 && y >= 0 && x < N && y < N;
}

int dfs(int x, int y)
{
	int i;
	int ret = 1;
	visited[x][y] = 1;
	for(i=0; i<4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if(inRange(nx, ny) && !visited[nx][ny] && A[nx][ny] > 0)
			ret += dfs(nx, ny);
	}
	return ret;
}

int getBiggest()
{
	int ret = 0;
	int i, j;

	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			if(A[i][j] > 0 && !visited[i][j])
				ret = max(ret, dfs(i, j));
	return ret;
}

int getSum()
{
	int i, j;
	int ret = 0;

	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			ret += A[i][j];
	return ret;
}

void melt(void)
{
	int i, j, k;
	int cnt;

	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
		{
			cnt = 0;
			for(k=0; k<4; k++)
			{
				int nx = i + dx[k];
				int ny = j + dy[k];
				if(!inRange(nx, ny))
					continue;
				else if(temp[nx][ny] > 0)
					cnt++;
			}

			A[i][j] = cnt<3 ? (temp[i][j] - 1) : temp[i][j];

		}
}




void rotate(int x, int y, int L)
{
	int i, j;
	int ys=0, xa=0;

	x *= L, y *= L;
	for(i=0; i<L; i++)
	{
		for(j=0; j<L; j++)
		{
			temp[x+(xa++)][y+L-1-ys] =A[x+i][y+j];
		}
		ys++;
		xa = 0;
	}
	/*
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
			printf("%d ", temp[i][j]);
		printf("\n");
	}
	*/
	return;
}

void solve(int L)
{
	int i, j;

	L = (1<<L);
	for(i = 0; i<N/L; i++)
		for(j=0; j<N/L; j++)
			rotate(i, j, L); // in temp
/*
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
			printf("%d ", temp[i][j]);
		printf("\n");
	}
*/
	melt();
}

int main(void)
{
	int i, j;
	

	scanf("%d %d", &N, &Q);
	N = (1<<N);

	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			scanf("%d", &A[i][j]);

	for(i=0; i<Q; i++)
	{
		scanf("%d", &L[i]);
		solve(L[i]);
	}

	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
			printf("%d ", A[i][j]);
		printf("\n");
	}
	printf("%d %d", getSum(), getBiggest());
	return 0;
}


