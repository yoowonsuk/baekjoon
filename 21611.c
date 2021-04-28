#include <stdio.h>

#define NMAX 49
#define MMAX 100

int map[NMAX][NMAX];
int arr[NMAX*NMAX];

int N, M;

int d[MMAX];
int s[MMAX];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int which;
int num;
int ans;

void score(int x, int y, int which) // which = 1 means map, which = 2 means arr & y -> count
{
	if(which == 1)
		ans+=map[x][y];
	else if(which == 2)
		ans+=arr[x]*y;
}

void maprint()
{
	int i, j;

	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
			printf("%d ", map[i][j]);
		printf("\n");
	}
	printf("\n");
}

void arrprint()
{
	int i;
	for(i=0; i<num; i++)
		printf("%d ", arr[i]);
	printf("\n");
}


void blizzard()
{
	int i;
	int x, y;

	x = y = (N-1)/2;

	for(i=0; i<s[which]; i++)
	{
		x += dx[d[which]];
		y += dy[d[which]];
		if(!map[x][y])
			break;
		score(x, y, 1);
		map[x][y] = -1;
	}
	which++;
}

void four()
{
	int i, j;
	int last;

	for(i=0; i<=num-3; i++)
		if(arr[i] == arr[i+1] && arr[i] == arr[i+2] && arr[i] == arr[i+3])
		{
			last = i+4;
			while(arr[i] == arr[last])
				last++;
			score(arr[i], last-i, 2);
			for(j=i; j<last; j++)
				arr[j] = -1;
			i = last-1;
		}	
}

void mapping(int what) // what = 1 map -> arr, what = 2 arr -> map
{
	int i, j;
	int k;
	int sign = -1, len = 1;
	int index = 0;
	int finish = 0;

	i = j = (N-1)/2;

	/* num means how many */
	while(what == 1)
	{
		for(k=0; k<len; k++)	
		{
			j += sign;
			if(map[i][j] == -1)
				continue;
			if(!map[i][j])
			{
				num = index;
				return;
			}
			arr[index++] = map[i][j];
		}

		sign *= -1;
		if(finish)
		{
			num = index;
			return;
		}
		for(k=0; k<len; k++)
		{
			i += sign;
			if(map[i][j] == -1)
				continue;
			if(!map[i][j])
			{
				num = index;
				return;
			}
			arr[index++] = map[i][j];
		}
		len++;
		if(len == N)
		{
			len--;
			finish++;
		}
	}
	while(what == 2)
	{
		for(k=0; k<len; k++)
		{
			j += sign;
			if(arr[index] == -1)
				continue;
			if(!arr[index])
			{
				num = index;
				return;
			}
			map[i][j] = arr[index++];
		}
		if(i == 1 && j == 1)
		{
			num = index;
			return;
		}
		sign *=-1;
		for(k=0; k<len; k++)
		{
			i+= sign;
			if(arr[index] == -1)
				continue;
			if(!arr[index])
			{
				num = index;
				return;
			}
			map[i][j] = arr[index++];
		}
		len++;
		if(len == N)
			len--;
	}
}

void solve()
{
	int i;

	for(i=0; i<M; i++)
	{
		blizzard();
		mapping(1);
		four();
		arrprint();
		mapping(2);
		maprint();
	}
}


int main(void)
{
	int i, j;
	scanf("%d %d", &N, &M);
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			scanf("%d", &map[i][j]);
	for(i=0; i<M; i++)
	{
		scanf("%d %d", &d[i], &s[i]);
		d[i]--;
	}

	solve();
	printf("%d", ans);
	return 0;
}


