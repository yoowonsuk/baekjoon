#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

typedef struct
{
  int x;
  int y;
  int r;
} Circle;

typedef struct
{
  int x;
  int y;
} Pos;

int inner(double dis, int r)
{
  if(dis < (double)r)
    return TRUE;
  else
    return FALSE;
}

int pass(Circle * ptr, Pos * pos1, Pos * pos2, int len)
{
  int num = 0, n1, n2, i;
  double dis1, dis2;

  for(i=0; i<len; i++)
  {
    dis1 = sqrt( pow(ptr[i].x-(pos1->x), 2) + pow(ptr[i].y-(pos1->y), 2) );
    dis2 = sqrt( pow(ptr[i].x-(pos2->x), 2) + pow(ptr[i].y-(pos2->y), 2) );
    n1 = inner(dis1, ptr[i].r);
    n2 = inner(dis2, ptr[i].r);
    if(n1 != n2)
      num++;
  }
  return num;
}

int main(void)
{
  int cnt, len, i;
  Circle * ptr = NULL;
  Pos prince, rose;

  scanf("%d", &cnt);
  while(cnt--)
  {
    scanf("%d %d %d %d", &(prince.x), &(prince.y), &(rose.x), &(rose.y));
    scanf("%d", &len);
    ptr = (Circle *)malloc(sizeof(Circle) * len);
    for(i=0; i<len; i++)
      scanf("%d %d %d", &(ptr[i].x), &(ptr[i].y), &(ptr[i].r));
    printf("%d\n", pass(ptr, &prince, &rose, len));
    free(ptr);
  }

  return 0;
}
