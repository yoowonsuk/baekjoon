#include <stdio.h>
#include <queue>
#include <cstring>

using namespace std;

#define NMAX 20

int N, M, fuel;

typedef struct
{
	int done, dist;
} Visit;

Visit visit[NMAX][NMAX] = {0}; // visit
int mymap[NMAX][NMAX] = {0}; // block

typedef struct
{
	int x, y, desx, desy, dist;
} People;

People person[NMAX*NMAX];

int taxi[2];

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};

int isBound(int x, int y)
{
	return x >= 0 && y >= 0 && x < N && y < N;
}

int first_cus;
int to_cus_fuel;

void BFS(People * who)
{
	int x, y;
	int i, j;
	People temp;

	memset(visit, 0, sizeof(visit));
	visit[who->x][who->y].done = 1;
	queue<People> q;
	q.push( (People) {who->x, who->y, -1, -1, -1} );
	while(1)
	{
		if(q.empty())
		{
			fuel = -1;
			return;
		}
		temp = q.front();
		q.pop();

		for(i=0; i<4; i++)
		{
			x = temp.x + dx[i];
			y = temp.y + dy[i];
			if(!isBound(x, y))
				continue;
			else if(visit[x][y].done == 1)
				continue;
			else if(mymap[x][y] == 1)
				continue;
			else if(who-> desx == -1)
			{
				for(j=0; j<M; j++)
				{
					if(person[j].x == x && person[j].y == y)
					{
						first_cus = j;
						to_cus_fuel = visit[temp.x][temp.y].dist + 1; 
						person[j].x = person[j].y = -1;
						return;
					}
				}
			}
			else if(x == who->desx && y == who->desy)
			{
				who->dist = visit[temp.x][temp.y].dist + 1;
				return;
			}

			visit[x][y].done = 1;
			visit[x][y].dist = visit[temp.x][temp.y].dist + 1;
			q.push( (People) {x, y, -1, -1, -1} );
		}
	}

}

void plen(void)
{
	int i;

	for(i=0; i<M; i++)
	{
		BFS(&person[i]);
		if(fuel == -1)
			return;
	}

}

/* it's work but make more simple
void plen(void)
{
	int i, j;
	int x, y;
	People temp;

	for(i=0; i<M; i++)
	{
		memset(visit, 0, sizeof(visit));
		visit[person[i].x][person[i].y].done = 1;
		queue<People> q;
		q.push( (People) {person[i].x, person[i].y, -1, -1, -1} );
		while(1)
		{
			temp = q.front();
			q.pop();
			for(j=0; j<4; j++)
			{
				x = temp.x + dx[j];
				y = temp.y + dy[j];
				if(!isBound(x, y))
					continue;
				else if(visit[x][y].done == 1)
					continue;
				else if(mymap[x][y] == 1)
					continue;
				else if(x == person[i].desx && y == person[i].desy)
				{
					person[i].dist = visit[temp.x][temp.y].dist + 1;
					break;
				}

				visit[x][y].done = 1;
				visit[x][y].dist = visit[temp.x][temp.y].dist + 1;
				q.push( (People) {x, y, -1, -1, -1} );
			}
			if(person[i].dist)
				break;
		}
	}
}
*/


void find_cus()
{
	int i;
	for(i=0; i<M; i++)
		if(person[i].x == taxi[0] && person[i].y == taxi[1])
		{
			first_cus = i;
			to_cus_fuel = 0;
			person[i].x = person[i].y = -1;
			return;
		}

	People temp = {taxi[0], taxi[1], -1, -1, -1};
	BFS( (People*) &temp );
}

void go()
{
	if(fuel >= to_cus_fuel + person[first_cus].dist)
	{
		fuel -= to_cus_fuel;
		fuel += person[first_cus].dist;
		taxi[0] = person[first_cus].desx, taxi[1] = person[first_cus].desy;
	}
	else
		fuel = -1;
}
		
void solve(void)
{
	int i;

	plen();
	for(i=0; i<M; i++)
	{	
		if(fuel == -1)
			return;
		find_cus();
		go();
	}
}

int main(void)
{
	int i, j;

	scanf("%d %d %d", &N, &M, &fuel);
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			scanf("%d", &mymap[i][j]);

	scanf("%d %d", &taxi[0], &taxi[1]);
	taxi[0]--, taxi[1]--;
	for(i=0; i<M; i++)
	{
		scanf("%d %d %d %d", &person[i].x, &person[i].y, &person[i].desx, &person[i].desy);
		person[i].x--;
		person[i].y--;
		person[i].desx--;
		person[i].desy--;
	}
	solve();

	printf("%d", fuel);
	return 0;
}
