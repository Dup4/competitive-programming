#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll a, b, x, n;
inline ll qmod(ll base, ll n, ll p) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % p;
        base = base * base % p;
        n >>= 1;
    }
    return res;
}

inline ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll ex_gcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0 && b == 0)
        return -1;
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = ex_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

inline ll inv(ll a, ll n) {
    ll x, y;
    ll d = ex_gcd(a, n, x, y);
    if (d == 1)
        return (x % n + n) % n;
    return -1;
}

inline void out(int x) {
    if (x == -1)
        puts("No Solution");
    else
        printf("%d\n", x);
}

struct Hash {
    static const int MOD = 564287;
    static const int N = 1e6;
    int head[MOD + 10], nx[MOD + 10], top;
    int hs[MOD + 10], id[MOD + 10];
    void init() {
        memset(head, 0, sizeof head);
        top = 0;
    }
    void insert(int x, int y) {
        int k = x % MOD;
        hs[top] = x;
        id[top] = y;
        nx[top] = head[k];
        head[k] = top++;
    }
    int find(int x) {
        int k = x % MOD;
        for (int i = head[k]; i; i = nx[i]) {
            if (hs[i] == x) {
                return id[i];
            }
        }
        return -1;
    }
} hs;

struct EX_BSGS {
    ll V, m, lim, n;
    inline ll getsqrt(ll n) {
        //适当更改块的大小和Hash的块的大小
        ll x = (ll)pow(n, 1.0 / 2);
        return x;
    }
    inline void init(ll a, ll _n) {
        n = _n;
        hs.init();
        m = getsqrt(n);
        lim = n / m + 1;
        V = inv(qmod(a, m, n), n);
        hs.insert(1, 0);
        ll e = 1;
        for (int i = 1; i < m; ++i) {
            e = e * a % n;
            if (hs.find(e) == -1) {
                hs.insert(e, i);
            }
        }
    }
    // a^x = b % n
    //不需要保证gcd(a, n) = 1
    //如果有解输出的是最小的正整数解，否则输出-1
    inline ll cal(ll a, ll b, ll n) {
        if (b == 1)
            return 0;
        int cnt = 0;
        ll t = 1;
        for (int d = gcd(a, n); d != 1; d = gcd(a, n)) {
            // b不是d的倍数，那么无解
            if (b % d)
                return -1;
            ++cnt;
            b /= d;
            n /= d;
            t = t * a / d % n;
            if (b == t)
                return cnt;
        }
        //下面就转换成了BSGS问题
        b = b * inv(t, n) % n;
        init(a, n);
        for (int i = 0; i < lim; ++i) {
            int j = hs.find(b);
            if (j != -1)
                return 1ll * i * m + j + cnt;
            b = V * b % n;
        }
        return -1;
    }
} exbsgs;

int main() {
    while (scanf("%lld%lld%lld", &a, &n, &b) != EOF) {
        if (a == 0 && b == 0 && n == 0)
            break;
        a %= n;
        b %= n;
        out(exbsgs.cal(a, b, n));
    }
    return 0;
}
