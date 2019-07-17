#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int * fibonacci(int n)
{
  static int arr[40][2] = {1, 0, 0, 1};
  int i;

    if (n == 0)
      return arr[0];
    else if (n == 1)
      return arr[1];
    else
      for(i=2; i<=n; i++)
      {
        arr[i][0] = arr[i-1][0] + arr[i-2][0];
        arr[i][1] = arr[i-1][1] + arr[i-2][1];
      }
    return arr[n];
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
