#include <stdio.h>
#include <string.h>

#define NMAX 50
#define MMAX 100

void mapprint();

int dx[] = {0, -1, -1, -1, 0, 1, 1, 1};
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

typedef struct
{
	int pond, cloud;
} MAP;

MAP map[NMAX][NMAX];
//MAP temp[NMAX][NMAX];

typedef struct
{
	int x, y;
} Data;

Data data[NMAX*NMAX];

int d[MMAX];
int s[MMAX];

int N, M;
int ans;
int which = -1;
int cloudnum = 4;

int isBound(int x, int y)
{
	return x>=0 && y>=0 && x<N && y<N;
}


void cloudmove()
{
	int tempx, tempy;
	int i, j;
	int num = 0;

	which++;
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			if(map[i][j].cloud)
			{
				tempx = i + dx[d[which]] * s[which];
				tempy = j + dy[d[which]] * s[which];

				while(tempx < 0)
					tempx += N;
				while(tempx >= N)
					tempx -= N;

				while(tempy < 0)
					tempy += N;
				while(tempy >= N)
					tempy -= N;

				map[i][j].cloud = 0;
				//temp[tempx][tempy].cloud = 1;
				data[num].x = tempx;
				data[num].y = tempy;
				num++;

				if(num == cloudnum)
				{
					/*
					int i, j;
					num = 0;
					for(i=0; i<N; i++)
						for(j=0; j<N; j++)
						{
							if(temp[i][j].cloud)
							{
								map[i][j].cloud = temp[i][j].cloud;
								num++;
								if(num == cloudnum)
								{
									memset(temp, 0, sizeof(temp));
									return;
								}
							}
						}
					*/
					while(num)
					{
						num--;
						map[data[num.x]][data[num].y].cloud = 1;
					}
					return;
				}

			}
}
				
void rain(void)
{
	int i, j, k;
	int num = 0;
	int tempx, tempy;

	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			if(map[i][j].cloud)
			{
				map[i][j].pond++;
				for(k=0; k<4; k++)
				{
					tempx = i + dx[2*k + 1];
					tempy = j + dy[2*k + 1];
					if(!isBound(tempx, tempy))
						continue;
					else if(map[tempx][tempy].pond || map[tempx][tempy].cloud)
						map[i][j].pond++;
				}

				num++;
				if(num == cloudnum)
					return;
			}
}

void makecloud()
{
	int i, j;
	cloudnum = 0;
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			if(map[i][j].cloud)
				map[i][j].cloud = 0;
			else if(!map[i][j].cloud && map[i][j].pond>1)
			{
				map[i][j].cloud = 1;
				map[i][j].pond -= 2;
				cloudnum++;
			}
}

void solve()
{
	int i;
	map[N-1][0].cloud = map[N-2][0].cloud = map[N-1][1].cloud = map[N-2][1].cloud = 1;


	for(i=0; i<M; i++)
	{
		cloudmove();
		rain();
		makecloud();
	}
}


void mapprint()
{
	int i, j;

	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
			printf("%d(%d) ", map[i][j].pond, map[i][j].cloud);
		printf("\n");
	}
	printf("\n");
}

void cal()
{
	int i, j;

	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			ans += map[i][j].pond;

}



int main(void)
{
	int i, j;
	scanf("%d %d", &N, &M);

	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			scanf("%d", &map[i][j].pond);

	for(i=0; i<M; i++)
	{
		scanf("%d %d", &d[i], &s[i]);
		d[i]--;
	}

	solve();
	cal();
	printf("%d", ans);
	return 0;
}
