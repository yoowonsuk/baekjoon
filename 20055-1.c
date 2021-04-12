#include <stdio.h>

#define NMAX 100

typedef struct
{
	int A, R;
} Belt;

Belt belt[2*NMAX] = {0};
Belt temp;

int N, K;
int kcount;

void land()
{
	belt[N-1].R = 0;
}

void on()
{
	if(belt[0].A)
	{
		belt[0].R = 1;
		belt[0].A--;
		if(!belt[0].A)
			kcount++;
	}
}

void rotate()
{
	int i;
	temp = belt[2*N-1];

	for(i=2*N-1; i>=1; i--)
		belt[i] = belt[i-1];
	belt[0] = temp;
	land();
}

void goRobot()
{
	int i;

	for(i=N-2; i>=1; i--)
		if(belt[i].R && !belt[i+1].R && belt[i+1].A)
		{
			belt[i].R = 0;
			belt[i+1].R = 1;
			belt[i+1].A--;
			if(!belt[i+1].A)
				kcount++;
		}
}

int main(void)
{
	int i;
	int count = 0;
	scanf("%d %d", &N, &K);
	
	for(i=0; i<2*N; i++)
		scanf("%d", &belt[i].A);

	while(kcount < K)
	{
		rotate();
		goRobot();
		on();
		count++;
	}

	printf("%d", count);
	return 0;
}
