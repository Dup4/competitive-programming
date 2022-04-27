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
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
using VI = vector<int>;
using VL = vector<ll>;
constexpr int mod = 1e9 + 7;
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
inline void pt(T s) {
    cout << s << "\n";
}
template <class T>
inline void pt(vector<T> &vec) {
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
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
constexpr int N = 1e6 + 10;
int n, a[N], ans[N];
pII f[N];
void run() {
    a[1 << n] = -mod;
    for (int i = 0; i < 1 << n; ++i) cin >> a[i];
    for (int i = 0; i < 1 << n; ++i) f[i] = pII(i, 1 << n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 1 << n; ++j) {
            if ((j >> i) & 1) {
                int k = j ^ (1 << i);
                if (a[f[k].fi] > a[f[j].fi]) {
                    f[j].se = f[j].fi;
                    f[j].fi = f[k].fi;
                    //	cout << j << " " << f[j].fi << " " << f[j].se << endl;
                }
                if (f[k].fi != f[j].fi && a[f[k].fi] > a[f[j].se]) {
                    f[j].se = f[k].fi;
                }
                if (f[k].se != f[j].fi && a[f[k].se] > a[f[j].se]) {
                    f[j].se = f[k].se;
                }
                //	cout << j << " " << f[j].fi << " " << f[j].se << endl;
            }
        }
    }
    memset(ans, 0, sizeof ans);
    for (int i = 1; i < 1 << n; ++i) {
        ans[i] = ans[i - 1];
        //	cout << i << " " << f[i].fi << " " << f[i].se << endl;
        if (f[i].fi != f[i].se && f[i].se != (1 << n)) {
            chmax(ans[i], a[f[i].fi] + a[f[i].se]);
        }
        pt(ans[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
