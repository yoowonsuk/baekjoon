#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define BUL_NUM 100
#define WAY_NUM 100

int search(int * bptr, int num, int (*mptr)[WAY_NUM], int way, int desti)
{
  int arr[BUL_NUM] = {0};
  int i, max = 0, result;

  if(arr[desti])
    return arr[desti];
  
  for(i=0; i<way; i++)
    if(mptr[i][desti])
    {
      result = search(bptr, num, mptr, way, i);
      if(result > max)
        max = result;
    }

  arr[desti] = bptr[desti] + max;
  return arr[desti];
}

int main(void)
{
   int i, j, cnt, num, xnum, ynum, desti, way;
   int bld[BUL_NUM];
   int met[WAY_NUM][WAY_NUM];

   scanf("%d", &cnt);
   while(cnt--)
   {
     // memset(met, 0, sizeof(met)); more than needs
     scanf("%d %d", &num, &way);

     for(i=0; i<way; i++)
       for(j=0; j<way; j++)
         met[i][j] = 0;

     for(i=0; i<num; i++)
       scanf("%d", &bld[i]);

     for(i=0; i<way; i++)
     {
       scanf("%d %d", &xnum, &ynum);
       met[xnum-1][ynum-1] = 1;
     }

     scanf("%d", &desti);

     printf("%d\n", search(bld, num, met, way, desti-1));
   }
   return 0;
}
