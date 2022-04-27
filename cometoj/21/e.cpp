#include <bits/stdc++.h>
using namespace std;

#define db long double
#define ll long long
#define N 400010
#define S 10010
const ll MOD = (ll)998244353;
int n, m, a[N], b[N], c[N];
vector<int> l[N], r[N];
ll ans[N];

void Hash() {
    c[0] = 0;
    for (int i = 0; i <= n; ++i) c[++c[0]] = a[i];
    for (int i = 0; i <= m; ++i) c[++c[0]] = b[i];
    sort(c + 1, c + 1 + c[0]);
    c[0] = unique(c + 1, c + 1 + c[0]) - c - 1;
    for (int i = 0; i <= n; ++i) a[i] = lower_bound(c + 1, c + 1 + c[0], a[i]) - c;
    for (int i = 0; i <= m; ++i) b[i] = lower_bound(c + 1, c + 1 + c[0], b[i]) - c;
}

ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = (res * base) % MOD;
        base = base * base % MOD;
        n >>= 1;
    }
    return res;
}

int x1[N], x2[N];
void ntt(int *a, int len, int f) {
    int i, j = 0, t, k;
    for (int i = 1; i < len - 1; ++i) {
        for (t = len; j ^= t >>= 1, ~j & t;)
            ;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int i = 1; i < len; i <<= 1) {
        t = i << 1;
        int wn = qmod(3, (MOD - 1) / t);
        for (int j = 0; j < len; j += t) {
            int w = 1;
            for (k = 0; k < i; ++k, w = 1ll * w * wn % MOD) {
                int x = a[j + k], y = 1ll * w * a[j + k + i] % MOD;
                a[j + k] = (x + y) % MOD, a[j + k + i] = (x - y + MOD) % MOD;
            }
        }
    }
    if (f == -1) {
        reverse(a + 1, a + len);
        int inv = qmod(len, MOD - 2);
        for (int i = 0; i < len; ++i) a[i] = 1ll * a[i] * inv % MOD;
    }
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i <= n; ++i) scanf("%d", a + i);
        for (int i = 0; i <= m; ++i) scanf("%d", b + i);
        Hash();
        for (int i = 0; i <= n; ++i) l[a[i]].push_back(i);
        for (int i = 0; i <= m; ++i) r[b[i]].push_back(i);
        int len1 = n + 1, len2 = m + 1, len = 1;
        while (len < (len1 + len2)) len <<= 1;
        memset(ans, 0, sizeof ans);
        for (int i = 1; i <= n + m + 5; ++i) {
            if (l[i].size() + r[i].size() < S) {
                for (auto u : l[i])
                    for (auto v : r[i]) ans[u + v] = (ans[u + v] + (1ll * u * v) % MOD) % MOD;
            } else {
                for (int j = 0; j < len; ++j) x1[j] = 0;
                for (int j = 0; j < len; ++j) x2[j] = 0;
                for (auto x : l[i]) x1[x] = x;
                for (auto x : r[i]) x2[x] = x;
                ntt(x1, len, 1);
                ntt(x2, len, 1);
                for (int j = 0; j < len; ++j) x1[j] = 1ll * x1[j] * x2[j] % MOD;
                ntt(x1, len, -1);
                for (int j = 0; j <= n + m; ++j) ans[j] = (ans[j] + x1[j]) % MOD;
            }
        }
        for (int i = 0; i <= n + m; ++i) printf("%lld%c", ans[i] % MOD, " \n"[i == n + m]);
    }
    return 0;
}
