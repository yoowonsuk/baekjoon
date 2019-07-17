#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int * fibonacci(int n)
{
  static int arr[40][2] = {1, 0, 0, 1};
  int * ptr1, * ptr2;

    if (arr[n][0] || arr[n][1])
      return arr[n];
    else
    {
      ptr1 = fibonacci(n-1);
      ptr2 = fibonacci(n-2);
      arr[n][0] = *ptr1 + *ptr2;
      arr[n][1] = *(ptr1+1) + *(ptr2+1);
      return arr[n];
    }
}

int main(void)
{
  int cnt, n;
  int * ptr;

  scanf("%d", &cnt);

  while(cnt--)
  {
    scanf("%d", &n);
    ptr = fibonacci(n);
    printf("%d %d\n", *ptr, *(ptr+1));
  }
  return 0;
}
