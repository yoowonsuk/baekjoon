#include <stdio.h>
#include <math.h>

int A[64][64] = {0};
int N;
int Q;
int L[6] = {0};
int temp[64][64] = {0};

/*
int pow (int a, int n)
{
	int i;
	int result = 1;

	for(i=0; i<n; i++)
		result *= a;
	return result;
}
*/

void rotate(int n, int m, int L)
{
	int i, j;
	int temp1 = 0, temp2=0;

	L = pow(2, L);
	for(i=n; i<n+L; i++)
	{
		for(j=m; j<m+L; j++)
			temp[n+(temp1++)][m+L-1-temp2] = A[i][j];
		
		temp2++;
		temp1 = 0;
	}
	for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++)
			printf("%d ", temp[i][j]);
		printf("\n");
	}
}

int main(void)
{
	int i, j, k;
	int count = 0, sum = 0;

	scanf("%d %d", &N, &Q);

	int n = pow(2, N);
	int m = 0;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			scanf("%d ", &A[i][j]);

	/*
	for(i=0; i<Q; i++)
		scanf("%d", &L[i]);
	*/
	for(i=0; i<Q; i++)
	{
		scanf("%d", &L[i]);
		/*
		for(j=0; j<n; j++)
			for(k=0; k<n; k++)
				temp[k][n-j] = A[j][k];
		*/
		m = pow(2, L[i]);
		m = n/m; // how many rotate = m*m

		for(j=0; j<m; j++)
			for(k=0; k<m; k++)
				rotate(2*j, 2*k, L[i]);
		
		// edge
		/*
		for(j=0; j<n; j++)
		{
			A[0][j] = temp[0][j] -1;
			A[n-1][j] = temp[n-1][j] -1;
			A[j][0] = temp[j][0] -1;
			A[j][n-1] = temp[j][n-1] - 1;
		}
		*/

		A[0][0] = temp[0][0] - 1;
		A[0][n-1] = temp[0][n-1] - 1;
		A[n-1][0] = temp[n-1][0] - 1;
		A[n-1][n-1] = temp[n-1][n-1] - 1;

		for(j=1; j<n-1; j++)
		{
			if(temp[0][j] == 0)
				A[0][j] = 0;
			else if(temp[0][j-1] != 0 && temp[0][j+1] != 0)
				A[0][j] = temp[1][j] > 0 ? temp[0][j] : temp[0][j] - 1;
			else
				A[0][j] = temp[0][j] - 1;

			if(temp[n-1][j] == 0)
				A[n-1][j] = 0;
			else if(temp[n-1][j-1] != 0 && temp[n-1][j+1] != 0)
				A[n-1][j] = temp[n-2][j] > 0 ? temp[n-1][j] : temp[n-1][j] - 1;
			else
				A[n-1][j] = temp[n-1][j] - 1;

			if(temp[j][0] == 0)
				A[j][0] = 0;
			else if(temp[j-1][0] != 0 && temp[j+1][0] != 0)
				A[j][0] = temp[j][1] > 0 ? temp[j][0] : temp[j][0] - 1;
			else
				A[j][0] = temp[j][0] - 1;

			if(temp[j][n-1] == 0)
				A[j][n-1] = 0;
			else if(temp[j-1][n-1] != 0 && temp[j+1][n-1] != 0)
				A[j][n-1] = temp[j][n-2] > 0 ? temp[j][n-1] : temp[j][n-1] - 1;
			else
				A[j][n-1] = temp[j][n-1] - 1;
		}
		// inner
		for(j=1; j<n-1; j++)
			for(k=1; k<n-1; k++)
			{
				if(temp[j-1][k] != 0 && temp[j+1][k] != 0)
				{
					if(temp[j][k-1] != 0 && temp[j][k+1] != 0)
						A[j][k] = temp[j][k];
				}
				else
					A[j][k] = temp[j][k] - 1;
			}
	}

	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
		{
			sum += A[i][j];
			if(0 < A[i][j])
				count++;
		}

	printf("%d\n%d\n", sum, count);
	return 0;
}
