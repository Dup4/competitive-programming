#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e7 + 10;
int pri[N], check[N], mu[N], pri_fac[N], fac[N];
ll n, m;
void sieve() {
    memset(check, 0, sizeof check);
    *pri = 0;
    mu[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            pri[++*pri] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= *pri; ++j) {
            if (1ll * i * pri[j] >= N)
                break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0) {
                mu[i * pri[j]] = 0;
                break;
            } else
                mu[i * pri[j]] = -mu[i];
        }
    }
    for (int i = 2; i < N; ++i) mu[i] += mu[i - 1];
}
void getfac(ll x) {
    *pri_fac = 0;
    for (int i = 1; 1ll * pri[i] * pri[i] <= x; ++i) {
        if (x % pri[i] == 0)
            pri_fac[++*pri_fac] = pri[i];
        while (x % pri[i] == 0) x /= pri[i];
    }
    if (x != 1)
        pri_fac[++*pri_fac] = x;
    int sze = *pri_fac;
    int S = 1 << sze;
    *fac = 0;
    for (int mask = 0; mask < S; ++mask) {
        int cnt = 0;
        ll num = 1;
        for (int j = 0; j < sze; ++j) {
            if ((mask >> j) & 1) {
                num *= pri_fac[j + 1];
                ++cnt;
            }
        }
        if (cnt & 1)
            fac[++*fac] = -num;
        else
            fac[++*fac] = num;
    }
    sort(fac + 1, fac + 1 + *fac, [&](int x, int y) {
        return abs(x) < abs(y);
    });
}

ll Mu(ll n) {
    getfac(n);
    for (int i = 1; i <= *fac; ++i)
        if (n == abs(fac[i]))
            return fac[i] < 0 ? -1 : 1;
    return 0;
}

ll S(ll n, ll m) {
    if (m == 1) {
        ll res = 0;
        for (int i = 1, j; 1ll * i * i <= n; i = j + 1) {
            ll t = n / i / i;
            j = sqrt(n / t);
            res += t * (mu[j] - mu[i - 1]);
        }
        return res;
    }
    getfac(m);
    vector<int> vec;
    for (int i = 1; i <= *fac; ++i) vec.push_back(fac[i]);
    ll res = 0;
    for (auto &it : vec) {
        if (abs(it) > n)
            break;
        res += 1ll * (it < 0 ? -1 : 1) * S(n / abs(it), abs(it));
    }
    return res;
}

int main() {
    sieve();
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%lld%lld", &n, &m);
        printf("%lld\n", Mu(m) * S(n / m, m));
    }
    return 0;
}
