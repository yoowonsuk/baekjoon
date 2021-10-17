#include <stdio.h>
#include <string.h>

#define NMAX 10
#define MMAX 11

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
int C;
int N, M;

char desk[NMAX][MMAX];
int state[1 << MMAX];
int dp[NMAX][1 << MMAX];

void ret_bin()
{
	int i;
	for(i=0; i<(1<<MMAX); i++)
		state[i] = i;
}

void sol()
{
	int i, j, k;
	int a, b;
	int temp, flag, count, tempPast;
	int num;
	int result = 0;

	for(i=0; i<N; i++)
	{
		for(j=0; j<(1<<M); j++)
		{
			//temp = state[j];
			temp = j;
			flag = 0;
			count = 0;
			for(a = 0; a < M; a++)
			{
				if( (char)(temp % 2) == 1 &&  desk[i][a] == 'x' )
				{
					flag = 1;
					break;
				}
				else if( temp%2 == 1 && (temp/2)%2 == 1 && a < M-1) // next?
				{
					flag = 1;
					break;
				}
				else if(temp%2 == 1)
					count++;
				temp /= 2;
			}
			if(flag)
				continue;
			else if(!i) // i == 0
			{
				dp[i][j] = count;
				continue;
			}
			for(k=0; k<(1<<M); k++)
			{
				//tempPast = state[k];
				tempPast = k;
				//temp = state[j];
				temp = j;
				num = 1;
				if(!dp[i-1][tempPast]) // impossible
					continue;
				flag = 0;
				for(a = 0; a < M; a++)
				{
					num *= 2;
					if( temp % 2 ) // yes
					{
						if( (a > 0 && (tempPast / (num/4)) % 2 ) || ( a < M-1 && (tempPast / num)%2 ) ) // isDiagonal?
						{
							flag = 1;
							break;
						}
					}
					temp /= 2;
				}
				if(flag)
					continue;
				else
					dp[i][j] = MAX(dp[i][j], count+dp[i-1][k]);
			}
		}
	}

	for(i=0; i<(1<<M); i++)
		result = MAX(result, dp[N-1][i]);
	printf("%d\n", result);
}

int main(void)
{
	int i, j;

	scanf("%d", &C);
//	ret_bin();
	for(i=0; i<C; i++)
	{
		scanf("%d %d", &N, &M);
		for(j=0; j<N; j++)
			scanf("%s", desk[j]);
		sol();
		memset(dp, 0, sizeof(dp));
	}
	return 0;
}
