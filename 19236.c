#include <stdio.h>

#define MAX(A, B) (((A) > (B)) ? (A) : (B))

typedef struct
{
	int a, b; // a = 0 means empty && a = -1 means shark
} Map;

Map map[4][4];

int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};

int ans;

typedef struct
{
	int x, y, dead;
} Fish;

Fish fish[16];

int isBound(int x, int y)
{
	return x>=0 && y>=0 && x<4 && y<4;
}

void changeFish(int x, int y, int nx, int ny)
{
	Map temp = map[x][y];

	if(!map[nx][ny].a) // just go
	{
		map[x][y].a = 0; // map[x][y].b doesn't matter
		map[nx][ny] = temp;

		fish[ map[nx][ny].a -1 ].x = nx;
		fish[ map[nx][ny].a -1 ].y = ny;
	}
	else // swap
	{
		map[x][y] = map[nx][ny];
		map[nx][ny] = temp;

		Fish temp = fish[ map[x][y].a - 1];
		fish[ map[x][y].a - 1] = fish[ map[nx][ny].a - 1];
		fish[ map[nx][ny].a - 1] = temp;
	}
/*	
			{
				int i, j;
				for(i=0; i<4; i++)
				{
					for(j=0; j<4; j++)
						printf("%d(%d) ", map[i][j].a, map[i][j].b);
					printf("\n");
				}
			}
*/			
}

void moveFish()
{
	int i, j;
	int nx, ny;
	int d; // direction

	for(i=0; i<16; i++)
	{
		if(fish[i].dead)
			continue;
		else
		{
			d = map[fish[i].x][fish[i].y].b;

			for(j=0; j<8; j++)
			{
				nx = fish[i].x + dx[ d ];
				ny = fish[i].y + dy[ d ];
				if(isBound(nx, ny) && map[nx][ny].a != -1)
				{
					changeFish(fish[i].x, fish[i].y, nx, ny);
					map[ fish[i].x ][fish[i].y ].b = d;
					break;
				}
			
				if(d < 7)
					d += 1;
				else
					d = 0;
			}

			{
				int i, j;
				for(i=0; i<4; i++)
				{
					for(j=0; j<4; j++)
						printf("%d(%d) ", map[i][j].a, map[i][j].b);
					printf("\n");
				}
			}


		}
	}
}

void sharkTime(int x, int y, int nx, int ny, int fishNum, int which)
{
	if(which == 1)
	{
		fish[fishNum-1].dead = 1;
		map[x][y].a = 0;
		map[nx][ny].a = -1;
	}
	else if(which == 2)
	{
		fish[fishNum-1].dead = 0;
		map[x][y].a = -1;
		map[nx][ny].a = fishNum;
	}
/*
	{
		printf("%d\n", which);
		int i, j;
		for(i=0; i<4; i++)
		{
			for(j=0; j<4; j++)
				printf("%d(%d) ", map[i][j].a, map[i][j].b);
			printf("\n");
		}
	}
	*/
}

void DFS(int x, int y, int dir, int sum)
{
	int nx, ny;
	int i;
	int fishNum;

	ans = MAX(ans, sum);
	{
		nx = x + dx[dir];
		ny = y + dx[dir];
		if(!isBound(nx, ny))
			return;
	}
	
	moveFish();
/*
	{
		int i, j;
		for(i=0; i<4; i++)
		{
			for(j=0; j<4; j++)
				printf("%d(%d) ", map[i][j].a, map[i][j].b);
			printf("\n");
		}
	}
	*/
	for(i=0; i<3; i++)
	{
		if(!map[nx][ny].a)
			continue;
		else
		{
			fishNum = map[nx][ny].a;
			sharkTime(x, y, nx, ny, fishNum, 1);
			DFS(nx, ny, map[nx][ny].b, sum+fishNum);
			sharkTime(x, y, nx, ny, fishNum, 2);
		}

		nx = x + dx[dir] * (i+2);
		ny = y + dx[dir] * (i+2);
		if(!isBound(nx, ny))
			return;
	}
}


int main(void)
{
	int i, j;

	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
		{
			scanf("%d %d", &map[i][j].a, &map[i][j].b);
			if(map[i][j].b)
				map[i][j].b--;
			else
				map[i][j].b = 7;
			fish[ map[i][j].a -1 ].x = i;
			fish[ map[i][j].a -1 ].y = j;
		}

	fish[ map[0][0].a -1 ].dead = 1;
	map[0][0].a = -1;
	
	DFS(0, 0, map[0][0].b, map[0][0].a);
	printf("%d", ans);
	return 0;
}
