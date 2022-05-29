#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <algorithm>

using namespace std;

int dp[1001][32][2];

int main() {
	int T, W;
	int which[1001];
	scanf("%d %d", &T, &W);
	for (int i = 1; i <= T; i++)
		scanf("%d", &which[i]);

	for (int i = 1; i <= T; i++) {
		for (int j = 0; j <= W; j++) {
			if (!j) {
				dp[i][j][0] = dp[i - 1][j][0] + ((which[i] == 1) ? 1 : 0);
				continue;
			}

			if (which[i] == 1) {
				dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j - 1][1]) + 1;
				dp[i][j][1] = max(dp[i - 1][j - 1][0], dp[i - 1][j][1]);
			}
			else {
				dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j - 1][1]);
				dp[i][j][1] = max(dp[i - 1][j - 1][0], dp[i - 1][j][1]) + 1;
			}
		}
	}

	int ans = 0;
	for (int i = 0; i <= W; i++) {
		ans = max(ans, dp[T][i][0]);
		ans = max(ans, dp[T][i][1]);
	}

	printf("%d\n", ans);
	return 0;
}
