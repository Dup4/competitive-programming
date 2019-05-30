#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#define MOD 1000000007
#define MAX 101000
#define ll long long
void add(int &x, int y) {
    x += y;
    if (x >= MOD)
        x -= MOD;
    if (x < 0)
        x += MOD;
}
ll n, w[MAX << 1];
int blk;
int pri[MAX], tot, sf[MAX];
bool zs[MAX];
int id1[MAX], id2[MAX], m;
int g[MAX << 1], h[MAX << 1];
void pre(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!zs[i])
            pri[++tot] = i, sf[tot] = (sf[tot - 1] + i) % MOD;
        for (int j = 1; j <= tot && i * pri[j] <= n; ++j) {
            zs[i * pri[j]] = true;
            if (i % pri[j] == 0)
                break;
        }
    }
}
int S(ll x, int y) {
    if (x <= 1 || pri[y] > x)
        return 0;
    int k = (x <= blk) ? id1[x] : id2[n / x];
    int ret = ((g[k] - h[k] - sf[y - 1] + y - 1) % MOD + MOD) % MOD;
    if (y == 1)
        add(ret, 2);
    for (int i = y; i <= tot && 1ll * pri[i] * pri[i] <= x; ++i) {
        ll t1 = pri[i], t2 = 1ll * pri[i] * pri[i];
        for (int e = 1; t2 <= x; ++e, t1 = t2, t2 *= pri[i])
            add(ret, (1ll * (pri[i] ^ e) * S(x / t1, i + 1) + (pri[i] ^ (e + 1))) % MOD);
    }
    return ret;
}
int main() {
    scanf("%lld", &n);
    pre(blk = sqrt(n));
    for (ll i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        w[++m] = n / i;
        h[m] = (w[m] + MOD - 1) % MOD;
        g[m] = ((w[m] % MOD) * ((w[m] + 1) % MOD) / 2 - 1 + MOD) % MOD;
        if (w[m] <= blk)
            id1[w[m]] = m;
        else
            id2[n / w[m]] = m;
    }
    for (int j = 1; j <= tot; ++j)
        for (int i = 1; i <= m && 1ll * pri[j] * pri[j] <= w[i]; ++i) {
            int k = (w[i] / pri[j] <= blk) ? id1[w[i] / pri[j]] : id2[n / (w[i] / pri[j])];
            add(g[i], MOD - 1ll * pri[j] * (g[k] - sf[j - 1] + MOD) % MOD);
            add(h[i], MOD - (h[k] - (j - 1) + MOD) % MOD);
        }
    int ans = S(n, 1) + 1;
    printf("%d\n", ans);
    return 0;
}
