#include <stdio.h>

int combi[1000][1000];
/*
int Combi(int M, int N)
{
	if(M==N || N == 0)
		return 1;
	else if(combi[M][N])
		return combi[M][N];
	else
		return combi[M][N] = (combi[M-1][N-1] = Combi(M-1, N-1)) + (combi[M-1][N] = Combi(M-1, N));
}
*/

int hockey(int M, int N)
{
	printf("M:  %d,  N:  %d\n", M, N);
	if(M == N)
		return combi[M][N] = 1;
	else if(N == 0)
		return (combi[M][N] = 1) + hockey(M-1, N);
	else if(combi[M][N])
		return combi[M][N] + hockey(M-1, N);
	else
		return (combi[M][N] = hockey(M-1, N-1)) + hockey(M-1, N);

}
		

int Combi(int M, int N)
{
	if(N==0)
		return combi[M][N] = 1;
	else
		return combi[M][N] = hockey(M-1, N-1);	
}
int main(void)
{
	int i, T;
	int N, M;

	scanf("%d", &T);
	for(i=0; i<T; i++)
	{
		scanf("%d %d", &N, &M);
		printf("%d\n", Combi(M, N));
	}
	
	return 0;
}
	
