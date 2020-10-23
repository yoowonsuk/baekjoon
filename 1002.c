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
    int cnt, i = 0;
    double dis;
    Point jo, ba;
    int arr[3];

    scanf("%d", &cnt);
    while(cnt--)
    {
      scanf("%d %d %d", &jo.x, &jo.y, &jo.r);
      scanf("%d %d %d", &ba.x, &ba.y, &ba.r);
      //dis = sqrt( (jo.x-ba.x)*(jo.x-ba.x) + (jo.y-ba.y)*(jo.y-ba.y) );
      dis = sqrt( pow(jo.x-ba.x, 2) + pow(jo.y-ba.y, 2) );
      if(!dis)
        if(ba.r == jo.r)
          arr[i++] = -1;
        else
          arr[i++] = 0;
      else if(dis < jo.r)
        if(dis+ba.r < jo.r || ba.r > dis+jo.r)
          arr[i++] = 0;
        else if(dis+jo.r == ba.r || dis+ba.r == jo.r)
          arr[i++] = 1;
        else 
          arr[i++] = 2;
      else if(dis == jo.r)
        if(2*jo.r > ba.r)
          arr[i++] = 2;
        else if(2*jo.r == ba.r)
          arr[i++] = 1;
        else
          arr[i++] = 0;
      else
        if(dis > jo.r + ba.r || dis+jo.r < ba.r)
          arr[i++] = 0;
        else if(dis == jo.r + ba.r || dis+jo.r == ba.r)
          arr[i++] = 1;
        else
          arr[i++] = 2;
    }

    for(i=0; i<3; i++)
      printf("%d\n", arr[i]);
    return 0;
}
