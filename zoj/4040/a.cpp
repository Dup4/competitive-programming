#include <bits/stdc++.h>
using namespace std;

#define ll long long
mt19937_64 rd(time(0));
ll n;
ll gcd(ll a, ll b) {
    ll t;
    while (b) {
        t = a;
        a = b;
        b = t % b;
    }
    if (a >= 0) {
        return a;
    } else {
        return -a;
    }
}
ll mul(ll a, ll b, ll c) {
    a %= c, b %= c;
    return (a * b - (ll)((long double)a * b / c) * c + c) % c;
}
ll qmod(ll base, ll n, ll p) {
    ll res = 1;
    base %= p;
    while (n) {
        if (n & 1) {
            res = mul(res, base, p);
        }
        base = mul(base, base, p);
        n >>= 1;
    }
    return res;
}
const int S = 8;
bool check(ll a, ll n, ll x, ll t) {
    ll res = qmod(a, x, n);
    ll last = res;
    for (int i = 1; i <= t; ++i) {
        res = mul(res, res, n);
        if (res == 1 && last != 1 && last != n - 1) {
            return true;
        }
        last = res;
    }
    if (res != 1) {
        return true;
    } else {
        return false;
    }
}
bool Miller_Rabin(ll n) {
    if (n < 2) {
        return false;
    } else if (n == 2) {
        return true;
    } else if ((n & 1) == 0) {
        return false;
    }
    ll x = n - 1;
    ll t = 0;
    while ((x & 1) == 0) {
        x >>= 1;
        ++t;
    }
    for (int i = 0; i < S; ++i) {
        ll a = rd() % (n - 1) + 1;
        if (check(a, n, x, t)) {
            return false;
        }
    }
    return true;
}
ll fac[220];
int tot;
ll pollard_rho(ll x, ll c) {
    ll i = 1, k = 2;
    ll x0 = rd() % (x - 1) + 1;
    ll y = x0;
    while (1) {
        ++i;
        x0 = (mul(x0, x0, x) + c) % x;
        ll d = gcd(y - x0, x);
        if (d != 1 && d != x) {
            return d;
        }
        if (y == x0) {
            return x;
        }
        if (i == k) {
            y = x0;
            k += k;
        }
    }
}
void findfac(ll n, int k) {
    if (n == 1) {
        return;
    }
    if (Miller_Rabin(n)) {
        fac[++tot] = n;
        return;
    }
    ll p = n;
    int c = k;
    while (p == n) {
        p = pollard_rho(n, c--);
    }
    findfac(p, k);
    findfac(n / p, k);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld", &n);
        if (n & 1) {
            puts("2");
            continue;
        } else if (n == 2) {
            puts("4");
            continue;
        }
        tot = 0;
        findfac(n, 107);
        sort(fac + 1, fac + 1 + tot);
        vector<ll> vec;
        vec.push_back(1);
        int sze;
        for (int i = 1; i <= tot; ++i) {
            if (i == 1 || fac[i - 1] % fac[i]) {
                sze = vec.size();
            } else {
                fac[i] *= fac[i - 1];
            }
            for (int j = 0; j < sze; ++j) {
                vec.push_back(fac[i] * vec[j]);
            }
        }
        sort(vec.begin(), vec.end());
        ll res = 0;
        for (auto it : vec) {
            if (it <= res + 1) {
                res += it;
            } else {
                break;
            }
        }
        printf("%lld\n", res + 1);
    }
    return 0;
}
