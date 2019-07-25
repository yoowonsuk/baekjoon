#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define BLD_NUM 100

int search(int (*mptr)[BLD_NUM], int bptr[], int dp[], int node, int desti)
{
  int i, max = 0, result;

  if(dp[desti])
    return dp[desti];
  
  for(i=0; i<node; i++)
    if(mptr[i][desti])
    {
      result = search(mptr, bptr, dp, node, i);
      if(result > max)
        max = result;
    }

//  if(dp[desti] < bptr[desti] + max)
    dp[desti] = bptr[desti] + max;
  return dp[desti];
}

int main(void)
{
   int i, j, cnt, node, way, desti, x, y;
   int bld[BLD_NUM];
   int mat[BLD_NUM][BLD_NUM];
   int dp[BLD_NUM];

   scanf("%d", &cnt);
   while(cnt--)
   {
     // memset(met, 0, sizeof(met)); more than needs
     scanf("%d %d", &node, &way);

     for(i=0; i<node; i++)
       for(j=0; j<node; j++)
         mat[i][j] = 0;
     
     for(i=0; i<node; i++)
       dp[i] = 0;

     for(i=0; i<node; i++)
       scanf("%d", &bld[i]);

     for(i=0; i<way; i++)
     {
       scanf("%d %d", &x, &y);
       mat[x-1][y-1] = 1;
     }

     scanf("%d", &desti);

     printf("%d\n", search(mat, bld, dp, node, desti-1));
   }
   return 0;
}
