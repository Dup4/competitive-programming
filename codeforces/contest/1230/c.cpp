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
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
constexpr int N = 1e2 + 10;
int n, m, id[N], res, e[N][2];
void DFS(int cur) {
    if (cur > n) {
        int sum = 0;
        map<pII, int> mp;
        for (int i = 1, u, v; i <= m; ++i) {
            u = e[i][0], v = e[i][1];
            pII t = pII(id[u], id[v]);
            if (t.fi > t.se)
                swap(t.fi, t.se);
            if (mp.count(t) == 0) {
                ++sum;
                mp[t] = 1;
            }
        }
        chmax(res, sum);
        return;
    }
    for (int i = 1; i <= 6; ++i) {
        id[cur] = i;
        DFS(cur + 1);
    }
}
void run() {
    for (int i = 1; i <= m; ++i) cin >> e[i][0] >> e[i][1];
    res = 0;
    DFS(1);
    out(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
