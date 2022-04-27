#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define fi first
#define se second
#define endl "\n"
using ll = long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
using VI = vector<int>;
using VL = vector<ll>;
constexpr ll mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
}
template <class T1, class T2>
inline void chmax(T1 &x, T2 y) {
    if (x < y)
        x = y;
}
template <class T1, class T2>
inline void chmin(T1 &x, T2 y) {
    if (x > y)
        x = y;
}
inline int rd() {
    int x;
    cin >> x;
    return x;
}
template <class T>
inline void rd(T &x) {
    cin >> x;
}
template <class T>
inline void rd(vector<T> &vec) {
    for (auto &it : vec) cin >> it;
}
template <class T>
inline void out(T s) {
    cout << s << "\n";
}
template <class T>
inline void out(vector<T> &vec) {
    for (auto &it : vec) cout << it << " ";
    cout << endl;
}
inline ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
inline ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base;
        base = base * base;
        n >>= 1;
    }
    return res;
}
constexpr int N = 1e5 + 10;
int n, _T, sta[N];
ll f[N], g[N], k;
inline ll sum(ll a1, ll d, ll n) {
    ll an = a1 + (n - 1) * d;
    return (a1 + an) * n / 2;
}
void run() {
    cin >> k;
    for (int i = 1; i <= 9; ++i) {
        if (k > f[i])
            k -= f[i];
        else {
            ll l = qpow(10, i - 1), r = qpow(10, i) - 1, pos = l - 1;
            while (r - l >= 0) {
                ll mid = (l + r) >> 1;
                if (sum(g[i - 1] + i, i, mid - qpow(10, i - 1) + 1) < k) {
                    pos = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            ++pos;
            k -= sum(g[i - 1] + i, i, pos - qpow(10, i - 1));
            //	out(k);
            for (int o = 1; o <= 9; ++o) {
                if (k <= g[o]) {
                    k -= g[o - 1];
                    ll l = qpow(10, o - 1), r = qpow(10, o) - 1, pos = l - 1;
                    //		cout << l << " " << r << " " << k << endl;
                    while (r - l >= 0) {
                        ll mid = (l + r) >> 1;
                        if ((mid - qpow(10, o - 1) + 1) * o < k) {
                            pos = mid;
                            l = mid + 1;
                        } else {
                            r = mid - 1;
                        }
                    }
                    ++pos;
                    //    cout << pos << endl;
                    k -= (pos - qpow(10, o - 1)) * o;
                    *sta = 0;
                    while (pos) {
                        sta[++*sta] = pos % 10;
                        pos /= 10;
                    }
                    reverse(sta + 1, sta + 1 + *sta);
                    return out(sta[k]);
                }
            }
            return;
        }
    }
}

int main() {
    f[0] = g[0] = 0;
    f[1] = sum(1, 1, 9);
    g[1] = 9;
    for (int i = 2; i <= 9; ++i) {
        f[i] = sum(i + g[i - 1], i, qpow(10, i) - qpow(10, i - 1));
        g[i] = g[i - 1] + (qpow(10, i) - qpow(10, i - 1)) * i;
    }
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    cin >> _T;
    while (_T--) run();
    return 0;
}
