#include <stdio.h>

#define NMAX 20
#define MMAX ((NMAX)*(NMAX))

int N, M, k;

typedef struct
{
	int l, s, w; // location, smell, which
} Map;

Map map[NMAX][NMAX];

int direct[MMAX][4][4]; // direction

typedef struct
{
	int dead, x, y, d; // dead, x, y, direction
} Shark;

Shark shark[MMAX];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int left;
int count;

int isBound(int x, int y)
{
	return x >=0 && y >=0 && x <N && y <N;
}

void go()
{
	int i, j;
	int xtemp, ytemp, goback, done=0;

	for(i=0; i<M && done != left; i++)
	{
		if(shark[i].dead)
			continue;
		done++;
		goback = -1; // not yet
		for(j=0; j<4; j++)
		{
			xtemp = shark[i].x + dx[direct[i][shark[i].d][j]];
			ytemp = shark[i].y + dy[direct[i][shark[i].d][j]];

			//printf("%d %d %d %d %d\n", i+1, shark[i].x, shark[i].y, dx[direct[i][shark[i].d][j]], dy[direct[i][shark[i].d][j]]);

			if(!isBound(xtemp, ytemp))
				continue;
			else if(map[xtemp][ytemp].s)
			{
				if(map[xtemp][ytemp].w-1 == i && goback<0)
					goback = j;
				continue;
			}

			//printf("%d %d %d %d %d\n", i+1, shark[i].x, shark[i].y, dx[direct[i][shark[i].d][j]], dy[direct[i][shark[i].d][j]]);
			goback=-2; // find way
			break;
		} // chose xtemp, ytemp

		if(goback != -2) // return to my smell
		{
			//printf("&&&goback&&&");
			//printf("%d %d %d %d %d\n", i+1, shark[i].x, shark[i].y, dx[direct[i][shark[i].d][goback]], dy[direct[i][shark[i].d][goback]]);
			map[ shark[i].x ][shark[i]. y].l = 0;
			shark[i].x = shark[i].x + dx[ direct[i][shark[i].d][goback] ];
			shark[i].y = shark[i].y + dy[ direct[i][shark[i].d][goback] ];
			map[shark[i].x][shark[i].y].l = i+1;
			shark[i].d = direct[i][shark[i].d][goback];
		}
		else if(map[xtemp][ytemp].l) // go front but dead
		{
			if(map[xtemp][ytemp].l-1 > i) // i win
			{
				//printf("zzzzzzz %d %d %d %d\n", i+1, xtemp, ytemp, map[xtemp][ytemp].l);
				map[shark[i].x][shark[i].y].l = 0;
				map[xtemp][ytemp].l = i+1;
				shark[i].x = xtemp;
				shark[i].y = ytemp;
				shark[i].d = direct[i][shark[i].d][j];
				shark[ map[xtemp][ytemp].l -1 ].dead++;
			}
			else // i lose
			{
				map[shark[i].x][shark[i].y].l = 0;
				shark[i].dead++;
			}
			left--;
		}
		else // go front
		{	
			map[ shark[i].x ][shark[i].y].l = 0;
			map[ xtemp ][ytemp].l = i+1;
			shark[i].x = xtemp;
			shark[i].y = ytemp;
			shark[i].d = direct[i][shark[i].d][j];
		}
	}
}

void removesmell()
{
	int i, j;

	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			if(map[i][j].s)
				map[i][j].s--;
}

void addsmell()
{
	int i, done=0;
	for(i=0; i<M; i++)
	{
		if(shark[i].dead)
			continue;
		map[ shark[i].x ][ shark[i].y ].s = k;
		map[ shark[i].x ][ shark[i].y ].w = i+1;
		done++;
		if(done == left)
			break;
	}
}

void solve()
{
	left = M;
	int a, b;
	addsmell();
	while(left > 1 && count <= 1000)
	{
		go();
		removesmell();
		addsmell();
		count++;

		/*
		printf("***start***\n");
		for(a=0; a<N; a++)
		{
			for(b=0; b<N; b++)
				printf("%d ", map[a][b].s);
			printf("\n");
		}
		printf("***finish****\n");
		*/
	}
	if(count == 1001)
		count = -1;
}

int main(void)
{
	int i, j, l; // forloop

	scanf("%d %d %d", &N, &M, &k);

	for(i = 0; i < N; i++)
		for(j=0; j<N; j++)
		{
			scanf("%d", &map[i][j].l);
			if(map[i][j].l)
			{
				shark[ map[i][j].l-1 ].x = i;
				shark[ map[i][j].l-1 ].y = j;
			}
		}


	for(i=0; i<M; i++)
	{
		scanf("%d", &shark[i].d);
		shark[i].d--;
	}

	for(i=0; i<M; i++)
		for(j=0; j<4; j++)
			for(l=0; l<4; l++)
			{
				scanf("%d", &direct[i][j][l]);
				direct[i][j][l]--;
			}
	solve();
	printf("%d", count);
	return 0;
}
