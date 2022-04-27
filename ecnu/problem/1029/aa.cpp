#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int maxn = 4005;
int N, M;
LL dp[20][3000];
void dfs(int col, int row, int state, int next) {
    if (row == M) {
        dp[col + 1][next] += dp[col][state];
        return;
    }
    if (((1 << row) & state) > 0)
        dfs(col, row + 1, state, next);
    if (((1 << row) & state) == 0)
        dfs(col, row + 1, state, next | (1 << row));
    if ((row + 1) < M && (((1 << row) & state) == 0) && ((1 << (row + 1)) & state) == 0)
        dfs(col, row + 2, state, next);
}
int main() {
    while (cin >> N >> M) {
        if (N == 0 && M == 0)
            break;
        memset(dp, 0, sizeof(dp));
        dp[1][0] = 1;
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < (1 << M); j++) {
                if (dp[i][j])
                    dfs(i, 0, j, 0);
            }
        }
        cout << dp[N + 1][0] << endl;
    }
    return 0;
}
