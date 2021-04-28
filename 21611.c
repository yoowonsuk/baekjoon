#include <stdio.h>
#include <string.h>

#define NMAX 49
#define MMAX 100

int map[NMAX][NMAX];
int arr[NMAX*NMAX];
int temp[NMAX*NMAX];

int N, M;

int d[MMAX];
int s[MMAX];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int which;
int where;
int num;
int ans;
int done;

void score(int x, int y, int which) // which = 1 means map, which = 2 means arr & y -> count
{
	//if(which == 1)
	//	ans+=map[x][y];
	//else if(which == 2)
		ans+=arr[x]*y;

	/*
	if(which == 1)
		printf("ans: %d, map[x][y]: %d, x: %d, y: %d\n", ans, map[x][y], x, y);
	else
		printf("ans: %d, arr[x]: %d, x: %d, y: %d\n", ans, arr[x], x, y);
	*/
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

int isBound()
{
	while(arr[where] == -1)
		where++;
	return arr[where++];
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
		//score(x, y, 1);
		map[x][y] = -1;
	}
	which++;
}

int four()
{
	int i, j;
	int last;
	int count = 0;

	for(i=0; i<=num-3; i++)
		if(arr[i] == arr[i+1] && arr[i] == arr[i+2] && arr[i] == arr[i+3])
		{
			done = 0;
			last = i+4;
			while(arr[i] == arr[last])
				last++;
			//printf("which: %d, i: %d, last: %d\n", which, i, last);
			score(i, last-i, 2);
			count += (last-i);
			for(j=i; j<last; j++)
				arr[j] = -1;
			i = last;
		}	
	j = 0;
	for(i=0; i<num; i++)
		if(arr[i] != -1)
			arr[j++] = arr[i];
	//printf("num: %d, count: %d\n", num, count);
	num -= count;
}

void rearrange()
{
	int i=0, j;
	int tempwhich=0;

	//printf("num: %d\n", num);
	while(i<num)
	{
		j = i; // j is init
		while(arr[i] == arr[i+1] && i < num)
			i++;
		//printf("j: %d, i: %d, arr[j]: %d\n", j, i, arr[j]);
		//printf("i: %d, arr[i]: %d, arr[i+1]: %d\n", i, arr[i], arr[i+1]);
		temp[tempwhich++] = i-j+1;
		temp[tempwhich++] = arr[j];
		if(tempwhich == N*N-1)
			break;
		i++;
	}
	num = tempwhich;
	//printf("num: %d\n", num);
	for(i=0; i<num; i++)
		arr[i] = temp[i];
	arr[i] = 0;
}



void mapping(int what) // what = 1 map -> arr, what = 2 arr -> map
{
	int i, j;
	int k;
	int sign = -1, len = 1;
	int index = 0;
	int finish = 0;
	int temp;

	i = j = (N-1)/2;
	where = 0;

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
			temp = isBound();
			if(!temp)
				return;
			map[i][j] = temp;
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
			temp = isBound();
			if(!temp)
				return;
			map[i][j] = temp;
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
		blizzard(); // good
		mapping(1); // good
		done = 0;
		while(!done)
		{
			done = 1;
			four(); // good
		}
		memset(map, 0, sizeof(map));
		rearrange();
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


