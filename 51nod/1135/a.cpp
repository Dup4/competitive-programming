#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
vector<pII> getfac(ll x) {
    vector<pII> fac;
    for (int i = 2; 1ll * i * i <= x; ++i) {
        if (x % i == 0) {
            pII it = pII(i, 0);
            while (x % i == 0) {
                ++it.se;
                x /= i;
            }
            fac.push_back(it);
        }
    }
    if (x != 1)
        fac.push_back(pII(x, 1));
    return fac;
}

ll qpow(ll base, ll n, ll mod) {
    ll res = 1;
    base = base % mod;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}

int gao(int p) {
    if (p == 2)
        return 1;
    vector<pII> fac = getfac(p - 1);
    for (int g = 2; g < p; ++g) {
        int ok = 1;
        for (auto &it : fac) {
            int t = (p - 1) / it.fi;
            if (qpow(g, t, p) == 1) {
                ok = 0;
                break;
            }
        }
        if (ok)
            return g;
    }
    return -1;
}

int main() {
    int p;
    while (scanf("%d", &p) != EOF) {
        printf("%d\n", gao(p));
    }
    return 0;
}
