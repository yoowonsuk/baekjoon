#include <stdio.h>

#define NMAX 100

typedef struct
{
	int A, avail;
} Belt;

Belt belt[2][NMAX] = {0};
Belt temp[2][NMAX] = {0};

int N, K;
int kcount=0, answer = 0;

void isZero(int i, int j)
{
	if(!belt[i][j].A)
		kcount++;
}

void land()
{
	belt[0][N-1].avail = 0;
}

void beltRotate()
{
	int i, j;
	
	for(i=0; i<N-1; i++)
		temp[0][i+1] = belt[0][i];
	temp[1][N-1] = belt[0][N-1];
	temp[0][0] = belt[1][0];

	for(i=0; i<N-1; i++)
		temp[1][i] = belt[1][i+1];

	for(i=0; i<2; i++)
		for(j=0; j<N; j++)
			belt[i][j] = temp[i][j];

	land();
}

void robotRotate()
{
	int i;
	
	for(i=N-2; i>=1; i--)
		if(belt[0][i].avail && !belt[0][i+1].avail && belt[0][i+1].A)
		{
			belt[0][i].avail--;
			belt[0][i+1].avail++;
			belt[0][i+1].A--;
			isZero(0, i+1);
		}
	land();
}


void solve()
{
	while(kcount<K)
	{
		answer++;
		beltRotate();
		robotRotate();
		if(belt[0][0].A)
		{
			belt[0][0].avail = 1;
			belt[0][0].A--;
			isZero(0, 0);
		}
			
	}
}

int main(void)
{
	int i;
	scanf("%d %d", &N, &K);

	for(i=0; i<N; i++)
		scanf("%d", &belt[0][i].A);
	for(i=N-1; i>=0; i--)
		scanf("%d", &belt[1][i].A);

	solve();
	printf("%d", answer);
	return 0;
}

