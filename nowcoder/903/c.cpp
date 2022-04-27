#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e2 + 10;

int n;
ll arr[maxn];
ll sum[maxn];
ll dp[maxn][maxn];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        memset(dp, 0x3f, sizeof dp);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", arr + i);
        }
        for (int i = 1; i <= n; ++i) {
            dp[i][i] = 0;
        }
        for (int len = 2; len <= n; ++len) {
            for (int l = 1; l + len - 1 <= n; ++l) {
                int r = l + len - 1;
                for (int k = l; k <= r; ++k) {
                    if (k == l) {
                        dp[l][r] = min(dp[l][r], dp[k + 1][r] + (len - 1) * arr[k]);
                    } else if (k == r) {
                        dp[l][r] = min(dp[l][r], dp[l][k - 1] + (len - 1) * arr[k]);
                    } else {
                        dp[l][r] = min(dp[l][r], dp[l][k - 1] + dp[k + 1][r] + (len - 1) * arr[k]);
                    }
                }
            }
        }
        //		for (int i = 1; i <= n; ++i) {
        //			for (int j = 1; j <= n; ++j) {
        //				cout << i << " " << j << " " << dp[i][j] << endl;
        //			}
        //		}
        printf("%lld\n", dp[1][n]);
    }
    return 0;
}
