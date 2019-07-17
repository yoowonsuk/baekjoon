#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int fibonacci(int n)
{
  static int arr[80] = {0, 1};
  
   if(n == -1)
     return 1;
   else if(!n)
     return 0;
   else if (arr[n])
     return arr[n];
   else
     return arr[n] = fibonacci(n-1) + fibonacci(n-2);
}

int main(void)
{
  int n, cnt;

  scanf("%d", &cnt);

  while(cnt--)
  {
    scanf("%d", &n);
    printf("%d %d\n", fibonacci(n-1), fibonacci(n));
  }
  return 0;
}
