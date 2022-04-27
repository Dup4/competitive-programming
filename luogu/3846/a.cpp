#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll a, b, x, p;

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

inline ll inv(ll x, ll p) {
    return qmod(x, p - 2, p);
}

struct Hash {
    static const int MOD = 1999997;
    static const int N = 1e6;
    int head[MOD + 10], nx[N], top;
    int hs[N], id[N];
    void init() {
        memset(head, -1, sizeof head);
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
        for (int i = head[k]; i != -1; i = nx[i]) {
            if (hs[i] == x) {
                return id[i];
            }
        }
        return -1;
    }
} hs;

struct BSGS {
    ll V, m, lim;
    inline ll getsqrt(int n) {
        //适当更改块的大小和Hash的块的大小
        ll x = (ll)pow(n, 1.0 / 2);
        return x;
    }
    inline void init(ll a, ll n) {
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
    //需要保证gcd(a, n) = 1, 即存在逆元
    inline ll cal(int b, int n) {
        if (b == 1)
            return 0;
        for (int i = 0; i < lim; ++i) {
            int j = hs.find(b);
            if (j != -1)
                return 1ll * i * m + j;
            b = V * b % n;
        }
        return -1;
    }
} bsgs;

int main() {
    while (scanf("%lld%lld%lld", &p, &a, &b) != EOF) {
        bsgs.init(a, p);
        x = bsgs.cal(b, p);
        if (x == -1)
            puts("no solution");
        else
            printf("%lld\n", x);
    }
    return 0;
}
