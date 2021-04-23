#include <stdio.h>

int N;
int list[3];
int pts, many;

int map[11][11];


void green()
{
	int i;

	if(list[0] == 1)
	{
		for(i=5; i<=9; i++)
			if(!map[i][list[2]] && map[i+1][list[2]])
			{
				map[i][list[2]] = 1;
				break;
			}
	}
	else if(list[0] == 2) // horizontal
	{
		for(i=5; i<=9; i++)
			if(!map[i][list[2]] && !map[i][list[2]+1] && (map[i+1][list[2]] || map[i+1][list[2]+1]))
			{
				map[i][list[2]] = map[i][list[2]+1] = 1;
				break;
			}
	}
	else // vertical
		for(i=5; i<=9; i++)
			if(!map[i][list[2]] && map[i+1][list[2]])
			{
				map[i][list[2]] = map[i-1][list[2]] = 1;
				break;
			}
	

	/*
	if(list[0] == 1)
	{
		for(i=9; i>=5; i--)
			if(!map[i][list[2]])
			{
				map[i][list[2]] = 1;
				break;
			}
	}
	else if(list[0] == 2) // horizontal
	{
		for(i=9; i>=5; i--)
			if(!map[i][list[2]] && !map[i][list[2]+1])
			{
				map[i][list[2]] = map[i][list[2]+1] = 1;
				break;
			}
	}
	else 
		for(i=9; i>=5; i--)
			if(!map[i][list[2]])
			{
				map[i][list[2]] = map[i-1][list[2]] = 1;
				break;
			}
	*/
}

void blue()
{
	int i;

	if(list[0] == 1)
	{
		for(i=5; i<=9; i++)
			if(!map[list[1]][i] && map[list[1]][i+1])
			{
				map[list[1]][i] = 1;
				break;
			}
	}
	else if(list[0] == 3) // vertical
	{
		for(i=5; i<=9; i++)
			if(!map[list[1]][i] && !map[list[1]+1][i] && (map[list[1]][i+1] || map[list[1]+1][i+1]))
			{
				map[list[1]][i] = map[list[1]+1][i] = 1;
				break;
			}
	}
	else
		for(i=5; i<=9; i++)
			if(!map[list[1]][i] && map[list[1]][i+1])
			{
				map[list[1]][i] = map[list[1]][i-1] = 1;
				break;
			}




	/*
	if(list[0] == 1)
	{
		for(i=9; i>=5; i--)
			if(!map[list[1]][i])
			{
				map[list[1]][i] = 1;
				break;
			}
	}
	else if(list[0] == 3) // vertical
	{
		for(i=9; i>=5; i--)
			if(!map[list[1]][i] && !map[list[1]+1][i])
			{
				map[list[1]][i] = map[list[1]+1][i] = 1;
				break;
			}
	}
	else
		for(i=9; i>=5; i--)
			if(!map[list[1]][i])
			{
				map[list[1]][i] = map[list[1]][i-1] = 1;
				break;
			}
	*/
}

void gremove(int x)
{
	int i;

	for(i=x; i>=4; i--)
	{
		map[i][0] = map[i-1][0];
		map[i][1] = map[i-1][1];
		map[i][2] = map[i-1][2];
		map[i][3] = map[i-1][3];
	}
}

void bremove(int y)
{
	int i;

	for(i = y; i>=4; i--)
	{
		map[0][i] = map[0][i-1];
		map[1][i] = map[1][i-1];
		map[2][i] = map[2][i-1];
		map[3][i] = map[3][i-1];
	}
}

void bingo()
{
	int i=9, count = 4;

	// green
	while(count)
	{
		count--;
		if(map[i][0] && map[i][1] && map[i][2] && map[i][3])
		{
			pts++;
			gremove(i);
		}
		else
			i--;
	}	

	i = 9, count = 4;

	// blue
	while(count)
	{
		count--;
		if(map[0][i] && map[1][i] && map[2][i] && map[3][i])
		{
			pts++;
			bremove(i);
		}
		else
			i--;
	}
}

void rest()
{
	const int i=5;

	// green
	while(map[i][0] || map[i][1] || map[i][2] || map[i][3])
		gremove(9);
	
	// blue
	while(map[0][i] || map[1][i] || map[2][i] || map[3][i])
		bremove(9);
}
	

	
int main(void)
{
	int i, j;	

	scanf("%d", &N);

	for(i=0; i<11; i++)
		map[i][10] = map[10][i] = 1;

	for(i=0; i<N; i++)
	{
		scanf("%d", &list[0]);

		scanf("%d %d", &list[1], &list[2]);
		green();
		blue();
		bingo();
		rest();
		{
			int a, b;
			for(a = 0; a<10; a++)
			{
				for(b=0; b<10; b++)
					printf("%d ", map[a][b]);
				printf("\n");
			}
			printf("\n");
		}
	}

	for(i=9; i>=6; i--)
		for(j=0; j<4; j++)
		{
			if(map[i][j])
				many++;
			if(map[j][i])
				many++;
		}
	printf("%d\n%d", pts, many);
	return 0;
}
		

