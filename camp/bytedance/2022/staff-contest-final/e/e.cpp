#include <bits/stdc++.h>
#include <cstring>

using namespace std;

using ll = long long;

constexpr int mod = 998244353;
constexpr int N = 2e3 + 10;
int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n = 0;
    int k = 0;
    cin >> n >> k;

    memset(f, 0, sizeof f);

    f[0][1] = 1;

    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= n; j++) {
            if (j < n) {
                f[i][j] += 1ll * f[i - 1][j + 1] * (j + 1) % mod * (n - 1) % mod;
                f[i][j] %= mod;
            }

            f[i][j] += 1ll * f[i - 1][j] * j % mod;
            f[i][j] %= mod;

            if (j > 0) {
                f[i][j] += 1ll * f[i - 1][j - 1] * (n - (j - 1)) % mod;
                f[i][j] %= mod;
            }
        }
    }

    ll res = 0;
    for (int i = 1; i <= n; i++) {
        res += f[k][i];
        res %= mod;
    }

    res *= n;
    res %= mod;

    cout << res << endl;

    return 0;
}
