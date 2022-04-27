#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e5 + 10;
int n, m, a[N], b[N], mod;

struct NTT {
    ll qpow(ll base, ll n, ll mod) {
        ll res = 1;
        while (n) {
            if (n & 1)
                res = res * base % mod;
            base = base * base % mod;
            n >>= 1;
        }
        return res;
    }
    ll inv(ll a, ll mod) {
        return qpow(a, mod - 2, mod);
    }
    ll mul(ll a, ll b, ll p) {
        a %= p, b %= p;
        return (a * b - (ll)(a / (long double)p * b + 1e-3) * p + p) % p;
    }
    static const int m1 = 469762049, m2 = 998244353, m3 = 1004535809, g = 3;
    static const ll M = 1ll * m1 * m2;
    int fn, fl, rev[N], goal[N];
    int c[N], d[N], ans[3][N];
    void init(int n) {
        fn = 1, fl = 0;
        while (fn <= n * 2) fn <<= 1, ++fl;
        for (int i = 0; i < fn; ++i) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (fl - 1));
        }
    }
    void work(int n, int *a, int opt, int mod) {
        for (int i = 0; i < n; ++i)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k <<= 1)
            for (int i = 0, wn = qpow(g, (mod - 1) / (k << 1), mod); i < n; i += (k << 1))
                for (int j = 0, w = 1, x, y; j < k; ++j, w = 1ll * w * wn % mod) {
                    x = a[i + j];
                    y = 1ll * w * a[i + j + k] % mod;
                    a[i + j] = (x + y) % mod;
                    a[i + j + k] = (x - y + mod) % mod;
                }
        if (opt == -1) {
            ll Inv = inv(n, mod);
            a[0] = 1ll * a[0] * Inv % mod;
            for (int i = 1; i <= n / 2; ++i) {
                a[i] = 1ll * a[i] * Inv % mod;
                if (i != n - i)
                    a[n - i] = 1ll * a[n - i] * Inv % mod;
                swap(a[i], a[n - i]);
            }
        }
    }
    //多组数据记得清空c[], d[]
    //满足模数可以分解成p = a2^k + 1形式
    //此处的n, m表示[0, n],[0, m]
    void gao(int *a, int *b, int n, int m) {
        init(max(n, m));
        copy(a, a + n + 1, c);
        copy(b, b + m + 1, d);
        work(fn, c, 1, mod);
        work(fn, d, 1, mod);
        for (int i = 0; i <= fn; ++i) goal[i] = 1ll * c[i] * d[i] % mod;
        work(fn, goal, -1, mod);
    }
    //任意模数
    void gao2(int *a, int *b, int n, int m) {
        init(max(n, m));
        copy(a, a + n + 1, c), copy(b, b + m + 1, d), work(fn, c, 1, m1), work(fn, d, 1, m1);
        for (int i = 0; i <= fn; ++i) ans[0][i] = 1ll * c[i] * d[i] % m1;
        memset(c, 0, sizeof c), memset(d, 0, sizeof d);
        copy(a, a + n + 1, c), copy(b, b + m + 1, d), work(fn, c, 1, m2), work(fn, d, 1, m2);
        for (int i = 0; i <= fn; ++i) ans[1][i] = 1ll * c[i] * d[i] % m2;
        memset(c, 0, sizeof c), memset(d, 0, sizeof d);
        copy(a, a + n + 1, c), copy(b, b + m + 1, d), work(fn, c, 1, m3), work(fn, d, 1, m3);
        for (int i = 0; i <= fn; ++i) ans[2][i] = 1ll * c[i] * d[i] % m3;
        work(fn, ans[0], -1, m1), work(fn, ans[1], -1, m2), work(fn, ans[2], -1, m3);
        for (int i = 0; i <= n + m; ++i) {
            ll A = (mul(1ll * ans[0][i] * m2 % M, qpow(m2 % m1, m1 - 2, m1), M) +
                           mul(1ll * ans[1][i] * m1 % M, qpow(m1 % m2, m2 - 2, m2), M)) %
                   M;
            ll k = ((ans[2][i] - A) % m3 + m3) % m3 * qpow(M % m3, m3 - 2, m3) % m3;
            goal[i] = ((k % mod) * (M % mod) % mod + A % mod) % mod;
        }
    }
} ntt;

int main() {
    scanf("%d%d%d", &n, &m, &mod);
    for (int i = 0; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i <= m; ++i) scanf("%d", &b[i]);
    ntt.gao2(a, b, n, m);
    for (int i = 0; i <= n + m; ++i) {
        printf("%d%c", ntt.goal[i], " \n"[i == n + m]);
    }
    return 0;
}
