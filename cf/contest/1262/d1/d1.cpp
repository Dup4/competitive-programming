#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n"
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
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
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
template <template <typename...> class T, typename t, typename... A>
void err(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
    err(args...);
}
void ptt() {
    cout << endl;
}
template <class T, class... Ts>
void ptt(const T &arg, const Ts &...args) {
    cout << ' ' << arg;
    ptt(args...);
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg;
    ptt(args...);
}
void pt() {}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1];
    pt(args...);
}
ll gcd(ll a, ll b) {
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
// head
constexpr int N = 1e2 + 10;
int n, a[N], b[N], q, k, pos;
void run() {
    vector<map<int, int>> has, nx;
    for (int i = 1; i <= n; ++i) cin >> a[i], b[i] = a[i];
    has.clear();
    has.resize(n + 5);
    nx.clear();
    nx.resize(n + 5);
    for (int i = 1; i <= n; ++i) nx[i + 1][a[i]] = n + 1, has[i + 1][a[i]] = 0;
    for (int i = n; i >= 0; --i) {
        has[i] = has[i + 1];
        nx[i] = nx[i + 1];
        if (i)
            ++has[i][a[i]];
        if (i < n)
            nx[i][a[i + 1]] = i + 1;
    }
    sort(b + 1, b + 1 + n);
    reverse(b + 1, b + 1 + n);
    cin >> q;
    for (int _q = 1; _q <= q; ++_q) {
        cin >> k >> pos;
        map<int, int> need;
        for (int i = 1; i <= k; ++i) {
            ++need[b[i]];
        }
        vector<int> vec;
        int pre = 0;
        for (int i = 1; i <= pos; ++i) {
            for (auto &it : need) {
                int nxPre = nx[pre][it.fi];
                int ok = 1;
                --it.se;
                for (auto &it1 : need) {
                    if (has[nxPre + 1][it1.fi] < it1.se) {
                        ok = 0;
                        break;
                    }
                }
                ++it.se;
                if (ok) {
                    --it.se;
                    vec.push_back(it.fi);
                    pre = nxPre;
                    if (it.se == 0)
                        need.erase(it.fi);
                    break;
                }
            }
        }
        pt(vec.back());
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
