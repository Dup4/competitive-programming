#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int n, m;
int dp[N][N];
char s[N], t[N];

// dp[i][j]表示s的前i个字符和t的前j个字符的编辑距离
int main() {
    while (scanf("%s%s", s + 1, t + 1) != EOF) {
        int n = (int)strlen(s + 1), m = (int)strlen(t + 1);
        for (int i = 0; i <= n; i++) {
            dp[i][0] = i;
        }
        for (int i = 0; i <= m; i++) {
            dp[0][i] = i;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (s[i] != t[j]));
            }
        }
        printf("%d\n", dp[n][m]);
    }
    return 0;
}
