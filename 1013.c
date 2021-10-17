#include <stdio.h>
#include <string.h>

#define FAIL 9

char arr[200];

int next[10][2] = {
	{6, 1}, // 0
	{2, FAIL},
	{3, FAIL},
	{3, 4},    // 3
	{6, 5},   
	{8, 5},
	{FAIL, 7},
	{6, 1},
	{3, 7};
	{FAIL, FAIL}
};

void sol()
{
	int state = 0;
	int i;
	char ch;

	for(i=0; i<strlen(arr); i++)
	{
		ch = arr[i] - '0';
		state = next[state][ch];
	}

	if(state == 4 || state == 5 || state == 7)
		printf("YES\n");
	else
		printf("NO\n");
}

int main(void)
{
	int T, i;

	scanf("%d", &T);
	for(i=0; i<T; i++)
	{
		scanf("%s", arr);
		sol();
	}
	return 0;
}
