#include <stdio.h>

static int map[2][10000];
static int N, W;
int a[10000], b[10000], c[10000];

int min(int n1, int n2)
{
  if(n1<n2)
    return n1;
  return n2;
}

void solution(int start)
{
  int i;

  for(i=start+1; i<=N; i++)
  {
    if(map[0][i-1] + map[1][i-1] <= W)
       a[i] = a[i-1]+1;
    else
      a[i] = a[i-1]+2;
    
    a[i] = min(a[i], b[i-1]+1);
    a[i] = min(a[i], c[i-1]+1);
    if(i-1>0)
      if(map[0][i-1]+map[0][i-2] <= W && map[1][i-1]+map[1][i-2] <= W)
        a[i] = min(a[i], a[i-2]+2);

    b[i] = a[i] + 1;
    b[i] = min(b[i], b[i-1]+2);
    if(map[0][i-1] + map[0][i] <= W)
      b[i] = min(b[i], c[i-1]+1);
    else
      b[i] = min(b[i], c[i-1]+2);

    c[i] = a[i] + 1;
    c[i] = min(c[i], c[i-1]+2);
    if(map[1][i-1] + map[1][i] <= W)
      c[i] = min(c[i], b[i-1]+1);
    else
      c[i] = min(c[i], b[i-1]+2);
  }
}



int main(void)
{
	int total;
  int i, j, result;

	scanf("%d", &total);

	while(total--)
	{
		scanf("%d %d", &N, &W);

    for(i=0; i<2; i++)
      for(j=0; j<N; j++)
        scanf("%d", &map[i][j]);

    a[0] = 0;
    b[0] = 1;
    c[0] = 1;
    solution(0);
    result = a[N];

    // [0][0] 제외
    // b[0] = 0; no meaning
    if(N > 1)
    {
      if(map[0][0] + map[0][N-1] <= W)
      {
        a[1] = 1;
        b[1] = 2;
        if(map[1][0] + map[1][1] <= W)
          c[1] = 1;
        else
          c[1] = 2;
        solution(1);
        result = result < c[N-1]+1 ? result : c[N-1]+1;
      }

      // [1][0] 제외
      // b[0] = 1; no meaning
      // c[0] = 0; no meaning
      // a[1] = 1; doesn't really need
      if(map[1][0] + map[1][N-1] <= W)
      {
        if(map[0][0] + map[0][1] <= W)
          b[1] = 1;
        else
          b[1] = 2;
        c[1] = 2;
        solution(1);
        result = result < b[N-1]+1 ? result : b[N-1]+1;
      }

      // [0][0] & [1][0] 제외
      if(map[0][0] + map[0][N-1] <= W && map[1][0] + map[1][N-1] <= W)
      {
        a[1] = 0;
        c[1] = b[1] = 1;
        solution(1);
        result = result < a[N-1]+2 ? result : a[N-1]+2;
      }
    }

    printf("%d\n", result);
  }
  return 0;
}
