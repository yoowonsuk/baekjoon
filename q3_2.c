#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct
{
  int x;
  int y;
  int r;
} Point;

int main(void)
{
    int cnt, where;
    double dis;
    Point jo, ba;

    scanf("%d", &cnt);
    while(cnt--)
    {
      scanf("%d %d %d", &jo.x, &jo.y, &jo.r);
      scanf("%d %d %d", &ba.x, &ba.y, &ba.r);
      //dis = sqrt( (jo.x-ba.x)*(jo.x-ba.x) + (jo.y-ba.y)*(jo.y-ba.y) );
      dis = sqrt( pow(jo.x-ba.x, 2) + pow(jo.y-ba.y, 2) );
      if(!dis && jo.r == ba.r)
        where = -1;
      else if(dis > (double)(jo.r+ba.r) || dis < (double)abs(jo.r-ba.r) )
        where = 0;
      else if(dis == (double)(jo.r+ba.r) || dis == (double)abs(jo.r-ba.r))
        where = 1;
      else
        where = 2;
      printf("%d\n", where);
    }

    return 0;
}
