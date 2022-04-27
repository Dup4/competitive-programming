#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 110
#define M 100010
#define pii pair<int, int>
#define fi first
#define se second
const ll p = 1e9 + 7;
int n, k;
ll f[N][M];
pii g[M];
map<int, int> mp;

int main() {
    while (scanf("%d%d", &k, &n) != EOF) {
        memset(f, 0, sizeof f);
        mp.clear();
        int m = 0;
        for (int i = 1, j; i <= k; i = j + 1) {
            j = k / (k / i);
            g[++m] = pii(j, j - i + 1);
            mp[j] = m;
        }
        for (int i = 1; i <= m; ++i) {
            f[1][i] = (f[1][i - 1] + g[i].se) % p;
        }
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                f[i][j] = (f[i][j - 1] + 1ll * g[j].se * f[i - 1][mp[k / g[j].fi]] % p) % p;
            }
        }
        printf("%lld\n", f[n][m]);
    }
    return 0;
}
