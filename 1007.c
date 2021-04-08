#include <stdio.h>
//#include <limits.h>
#include <float.h>
#include <math.h>

typedef struct
{
  int x;
  int y;
} pos;

pos data[20];
int c[20];
double result;
int N;

double min(double a, double b)
{
	return a < b ? a : b;
}

void solve(int cnt, int index)
{
	if(cnt == N/2)
	{
		int i;
		double x, y;
		x = y = 0.0;
		for(i=0; i<N; i++)
			if(c[i])
			{
				x -= data[i].x;
				y -= data[i].y;
			}
			else
			{
				x += data[i].x;
				y += data[i].y;
			}
		result = min(result, sqrt(x*x+y*y));
		return;
	}
	if(index == N)
		return;

	solve(cnt, index+1);
	c[index] = 1;
	solve(cnt + 1, index + 1);
	c[index] = 0;
}


int main(void)
{
	int i, j;
	int T;
  
	scanf("%d", &T);
  
	for(i=0; i<T; i++)
	{
		scanf("%d", &N);
		
		for(j=0; j<N; j++)
			scanf("%d %d", &data[j].x, &data[j].y);

		result = DBL_MAX;
		solve(0, 0);
		printf("%.6f\n", result);
	}
	return 0;
}


