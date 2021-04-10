#include <stdio.h>
#include <string.h>

#define NMAX 50

int N, M, K;

typedef struct
{
	int r, c, m, s , d;
} Fireball;

Fireball fire[NMAX*NMAX];

typedef struct
{
	int m, s, d, odd, even, count;
} Map;

Map map[NMAX][NMAX];

int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
int temp, time;

void initialize()
{
	memset(map, 0, sizeof(map));
}

void aftermove()
{
	int i, j, k;

	time = 0;
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			if(time == temp) // no more
				return;
			else if(map[i][j].count == 1)
			{
				Fireball temp = {i, j, map[i][j].m, map[i][j].s, map[i][j].d};
				fire[M++] = temp;
				time++;
			}
			else if(map[i][j].count > 1)
			{
				if(map[i][j].m / 5 == 0)
					continue;
				else if(map[i][j].odd && map[i][j].even) // both 1
					for(k=1; k<=7; k += 2)
					{
						Fireball temp = {i, j, map[i][j].m/5, map[i][j].s/map[i][j].count, k};
						fire[M++] = temp;
					}
				else
				{
					for(k=0; k<=6; k += 2)
					{
						Fireball temp = {i, j, map[i][j].m/5, map[i][j].s/map[i][j].count, k};
						fire[M++] = temp;
					}
				}
				time++;
			}
}

void move()
{
	temp = M;
	while(0 < M)
	{
		int go = fire[--M].s % N;
		int x = fire[M].r + dx[fire[M].d] * go;
		int y = fire[M].c + dy[fire[M].d] * go;
		if(x >= N)
			x -= N;
		else if(x < 0)
			x += N;
		if(y >= N)
			y -= N;
		else if(y < 0)
			y += N;
		if(map[x][y].d % 2 == 0) // even
			map[x][y].even = 1;
		else
			map[x][y].odd = 1;

		map[x][y].count++;
		map[x][y].m += fire[M].m;
		map[x][y].s = fire[M].s;
		map[x][y].d = fire[M].d;
	}
}

void around()
{
	move();
	aftermove();
	initialize();
}
		

int main(void)
{
	int i;
	int remain=0;
	
	scanf("%d %d %d", &N, &M, &K);

	for(i=0; i<M; i++)
	{
		scanf("%d %d %d %d %d", &fire[i].r, &fire[i].c, &fire[i].m, &fire[i].s, &fire[i].d);
		fire[i].r--;
		fire[i].c--;
	}
	
	for(i=0; i<K; i++)
		around();

	for(i=0; i<M; i++)
		remain += fire[i].m;
	printf("%d", remain);
	return 0;
}
