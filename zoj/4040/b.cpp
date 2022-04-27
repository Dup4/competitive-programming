#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int C = 2307;
const int S = 10;
typedef pair<ll, int> pli;
vector<pli> pri;
vector<ll> fac;

vector<ll> ve;
mt19937_64 rd(time(0));
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
ll mul(ll a, ll b, ll mod) {
    return (a * b - (ll)(a / (long double)mod * b + 1e-3) * mod + mod) % mod;
}
ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b) {
        if (b & 1)
            res = mul(res, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return res;
}
bool check(ll a, ll n) {
    ll m = n - 1, x, y;
    int j = 0;
    while (!(m & 1)) m >>= 1, j++;
    x = qpow(a, m, n);
    for (int i = 1; i <= j; x = y, i++) {
        y = mul(x, x, n);
        if (y == 1 && x != 1 && x != n - 1)
            return 1;
    }
    return y != 1;
}
bool miller_rabin(ll n) {
    ll a;
    if (n == 1)
        return 0;
    if (n == 2)
        return 1;
    if (!(n & 1))
        return 0;
    for (int i = 0; i < S; i++)
        if (check(rd() % (n - 1) + 1, n))
            return 0;
    return 1;
}
ll pollard_rho(ll n, int c) {
    ll i = 1, k = 2, x = rd() % n, y = x, d;
    while (1) {
        i++;
        x = (mul(x, x, n) + c) % n, d = gcd(y - x, n);
        if (d > 1 && d < n)
            return d;
        if (y == x)
            return n;
        if (i == k)
            y = x, k <<= 1;
    }
}
void findfac(ll n, int c) {
    if (n == 1)
        return;
    if (miller_rabin(n)) {
        ve.push_back(n);
        return;
    }
    ll m = n;
    while (m == n) m = pollard_rho(n, c--);
    findfac(m, c);
    findfac(n / m, c);
}
void solve(ll n) {
    vector<pli> res;
    ve.clear();
    pri.clear();
    findfac(n, C);
    sort(ve.begin(), ve.end());
    for (auto x : ve) {
        if (pri.empty() || pri.back().first != x)
            pri.push_back({x, 1});
        else
            pri.back().second++;
    }
}

int main() {
    int t;
    ll n;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        if (n & 1) {
            printf("2\n");
            continue;
        }
        if (n == 2) {
            printf("4\n");
            continue;
        }
        solve(n);
        ll ans = 1, tmp;
        fac.clear();
        fac.push_back(1);
        int sz = pri.size();
        for (auto it : pri) {
            ll p = it.first;
            ll tmp = 1;
            int sz = fac.size();
            for (int i = 1; i <= it.second; i++) {
                tmp *= p;
                for (int j = 0; j < sz; j++) {
                    fac.push_back(fac[j] * tmp);
                }
            }
        }
        sort(fac.begin(), fac.end());
        assert(fac.size() <= 20000);
        ll val = 0;
        for (auto i : fac) {
            if (i > val + 1)
                break;
            val += i;
        }
        printf("%lld\n", val + 1);
    }
}
