#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3e3 + 10;
const int mod = 1e9 + 7;
int n, a[N], fac[N], finv[N], cnt[10010];
ll res;
ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
inline ll inv(ll x) {
    return qpow(x, mod - 2);
}
bool DFS(int now, ll prod, ll sum, int cur, ll base) {
    int x = n - cur;
    if (prod - sum > x)
        return false;
    if (prod - sum == x) {
        res = (res + 1ll * fac[n] * inv(base) % mod * finv[x] % mod);
        res %= mod;
        return false;
    }
    for (int j = now;; ++j) {
        ll nbase = base;
        nbase = nbase * finv[cnt[j]] % mod;
        ++cnt[j];
        nbase = nbase * fac[cnt[j]] % mod;
        if (DFS(j, prod * j, sum + j, cur + 1, nbase)) {
            --cnt[j];
            return false;
        }
    }
    return true;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
    finv[N - 1] = qpow(fac[N - 1], mod - 2);
    for (int i = N - 1; i >= 1; --i) finv[i - 1] = 1ll * finv[i] * i % mod;
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        memset(cnt, 0, sizeof cnt);
        scanf("%d", &n);
        res = 0;
        DFS(2, 1, 0, 0, 1);
        printf("%lld\n", res);
    }
    return 0;
}
