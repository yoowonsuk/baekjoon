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

void copyState(Map m1[][4], Map m2[][4], Fish f1[], Fish f2[])
{
	int i, j;

	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			m2[i][j] = m1[i][j];
	for(i=0; i<16; i++)
		f2[i] = f1[i];
}

void DFS(int x, int y, int dir, int sum)
{
	int nx, ny;
	int i;
	int fishNum;
	Map C_MAP[4][4];
	Fish C_FISH[16];

	ans = MAX(ans, sum);
	{
		nx = x + dx[dir];
		ny = y + dy[dir];
		if(!isBound(nx, ny))
			return;
	}
	
	copyState(map, C_MAP, fish, C_FISH);
	moveFish();
	//copyState(map, C_MAP, fish, C_FISH);
	

	{
		printf("let's go %d\n", ans);
		int i, j;
		for(i=0; i<4; i++)
		{
			for(j=0; j<4; j++)
				printf("%d(%d) ", map[i][j].a, map[i][j].b);
			printf("\n");
		}
	}


	for(i=0; i<3; i++)
	{
		if(map[nx][ny].a)
		{
			fishNum = map[nx][ny].a;
			sharkTime(x, y, nx, ny, fishNum, 1);

		printf("before1\n");
			
	{
		int i, j;
		for(i=0; i<4; i++)
		{
			for(j=0; j<4; j++)
				printf("%d(%d) ", map[i][j].a, map[i][j].b);
			printf("\n");
		}
	}
		printf("after1\n");


			DFS(nx, ny, map[nx][ny].b, sum+fishNum);
			sharkTime(x, y, nx, ny, fishNum, 2);
		printf("before2\n");
	{
		int i, j;
		for(i=0; i<4; i++)
		{
			for(j=0; j<4; j++)
				printf("%d(%d) ", map[i][j].a, map[i][j].b);
			printf("\n");
		}
	}

		printf("after2\n");


		}

		nx = x + dx[dir] * (i+2);
		ny = y + dy[dir] * (i+2);
		if(!isBound(nx, ny))
			break;

	}

	copyState(C_MAP, map, C_FISH, fish);
}


int main(void)
{
	int i, j;
	int temp;

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

	/*
	{
		Map C_MAP[4][4];
		Fish C_FISH[16];
		copyState(map, C_MAP, fish, C_FISH);

		int i, j;
		sharkTime(0, 0, 1, 1, 12, 1);
		sharkTime(0, 0, 1, 1, 12, 2);

		for(i=0; i<4; i++)
		{
			for(j=0; j<4; j++)
				printf("%d ", C_MAP[i][j].a);
			printf("\n");
		}
	}
	*/







	fish[ map[0][0].a -1 ].dead = 1;
	temp = map[0][0].a;
	map[0][0].a = -1;
	
	DFS(0, 0, map[0][0].b, temp);
	printf("%d", ans);
	return 0;
}
