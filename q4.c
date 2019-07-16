#include <stdio.h>

int cnt0, cnt1;

int fibonacci(int n) {
    if (n == 0) {
      cnt0++;
        return 0;
    } else if (n == 1) {
      cnt1++;
        return 1;
    } else {
      return fibonacci(n-1) + fibonacci(n-2);
    }
}

int main(void)
{
  int num, figure;

  scanf("%d", &num);
  while(num--)
  {
    scanf("%d", &figure);
    fibonacci(figure);
    printf("%d %d\n", cnt0, cnt1);
    cnt0 = cnt1 - 0;
  }
  return 0;
}

