#include <stdio.h>

#define NMAX 20
#define MMAX ((NMAX)*(NMAX))

int N, M, k;

typedef struct
{
	int location, who, smell;
} Map;

Map map[NMAX][NMAX];

int direct[MMAX][4][4];

typedef struct
{
        int alive, x, y, direct;
} Shark;

Shark shark[MMAX];

int count = 0;
int left = 0; 

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int isBound(int x, int y)
{
	return x >= 0 && y >= 0 && x < M && y < M;
}

void mapsmell(void)
{
	int i, j;
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			if(map[i][j].smell)
				map[i][j].smell--;

	for(i=0; i<M; i++)
		if(shark[i].alive)
		{
			map[ shark[i].x ][ shark[i].y ].smell = k;
			map[ shark[i].x ][ shark[i].y ].who = i+1;
		}
}

void solve(void)
{
	int i, j;
	int xtemp, ytemp, fix, goback, fight;
	left = M;
	
	for(i=0; i<M; i++)
	{
		map[ shark[i].x ][ shark[i].y ].smell = k;
		map[ shark[i].x ][ shark[i].y ].who = i+1;
	}

	while(left > 1)
	{
		for(i=0; i<M; i++)
		{
			if(!shark[i].alive)
				continue;
			fix = 0;
			for(j=0; j<4; j++)
			{
				xtemp = shark[i].x + dx[ direct[ i ][ shark[i].direct ][j] ];
				ytemp = shark[i].y + dy[ direct[ i ][ shark[i].direct ][j] ];

				if(!isBound(xtemp, ytemp))
					continue;
				else if(map[xtemp][ytemp].smell)
				{
					if(!fix && i == map[xtemp][ytemp].who-1) // fix=0
					{
						fix++;
						goback = direct[i][shark[i].direct][j];
					}
					continue;
				}
				else if(j==3)
				{
					map[ shark[i].x ][ shark[i].y ].location = 0;
					shark[i].x += dx[goback];
					shark[i].y += dy[goback];
					shark[i].direct = goback;
					map[ shark[i].x ][ shark[i].y ].location = i+1;
				}	
				else if(map[xtemp][ytemp].location)
				{	
					fight = map[xtemp][ytemp].location;

					if(i > fight-1) // i lose
					{
						shark[i].alive = 0;
						map[ shark[i].x ][ shark[i].y ].location = 0;
					}
					else
					{
						shark[fight].alive = 0;
						map[ shark[i].x ][ shark[i].y ].location=0;
						shark[i].x += xtemp;
						shark[i].y += ytemp;
						shark[i].direct = direct[i][shark[i].direct][j];
						map[xtemp][ytemp].location = i+1;
					}
					left--;
					break;
				}
				//printf("%d %d %d\n", xtemp, ytemp, i+1); // where to go
				map[ shark[i].x ][ shark[i].y ].location = 0;
				map[xtemp][ytemp].location = i+1;
				shark[i].x = xtemp;
				shark[i].y = ytemp;
				shark[i].direct = direct[i][shark[i].direct][j];
				break;
			}
			count++;
			mapsmell();
		}
	}
}

int main(void)
{
        int i, j, k;
        scanf("%d %d %d", &N, &M, &k);

        for(i=0; i<N; i++)
                for(j=0; j<N; j++)
		{
                        scanf("%d", &map[i][j].location); // where are they
			if(map[i][j].location)
			{
				shark[ map[i][j].location -1 ].x = i;
				shark[ map[i][j].location -1 ].y = j;
			}
		}

        for(i=0; i<M; i++)
	{
		shark[i].alive = 1;
                scanf("%d", &shark[i].direct); // direction
		shark[i].direct--;
	}
        for(i=0; i<M; i++)
                for(j=0; j<4; j++)
                        for(k=0; k<4; k++)
			{
                                scanf("%d", &direct[i][j][k]); // control
				direct[i][j][k]--;
			}

        solve();
        printf("%d", count);
        return 0;
}
