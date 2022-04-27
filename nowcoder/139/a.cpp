#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1010
const ll p = 1e9 + 7;
int n, m;
ll f[N][N][3];
void add(ll &x, ll y) {
    x += y;
    if (x >= p)
        x -= p;
}

int main() {
    memset(f, 0, sizeof f);
    for (int i = 0; i < 3; ++i) f[1][1][i] = 1;
    for (int i = 2; i <= 1000; ++i) {
        ll tot = 0;
        for (int j = 0; j < 3; ++j) {
            add(tot, f[1][i - 1][j]);
            f[1][i][j] = tot;
            f[i][1][j] = tot;
        }
    }
    for (int i = 2; i <= 1000; ++i) {
        for (int j = 2; j <= 1000; ++j) {
            ll t[3] = {0};
            for (int k = 0; k < 3; ++k) {
                add(t[0], f[1][j - 1][k]);
                add(t[1], f[i - 1][1][k]);
                add(t[2], f[i - 1][j - 1][k]);
                f[i][j][k] = t[0] * t[1] % p * t[2] % p;
            }
        }
    }
    for (int i = 1; i <= 1000; ++i) {
        for (int j = 1; j <= 1000; ++j) {
            for (int k = 1; k < 3; ++k) {
                add(f[i][j][k], f[i][j][k - 1]);
            }
        }
    }
    while (scanf("%d%d", &n, &m) != EOF) {
        printf("%lld\n", f[n][m][2]);
    }
    return 0;
}
