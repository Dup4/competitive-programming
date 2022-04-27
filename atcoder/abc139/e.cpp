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
    if (x >= mod)
        x -= mod;
    else if (x < 0)
        x += mod;
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
constexpr int N = 1e3 + 10;
int n, used[N];
vector<vector<int>> a;
int gao() {
    bool F = 0;
    memset(used, 0, sizeof used);
    for (int i = 1; i <= n; ++i)
        if (!used[i] && !a[i].empty()) {
            int v = a[i].back();
            if (!used[v] and a[v].back() == i) {
                used[i] = 1;
                used[v] = 1;
                a[i].pop_back();
                a[v].pop_back();
                F = 1;
            }
        }
    return F;
}
bool done() {
    for (int i = 1; i <= n; ++i)
        if (!a[i].empty())
            return 0;
    return 1;
}
void run() {
    a.clear();
    a.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        a[i].clear();
        a[i].resize(n - 1);
        for (auto &it : a[i]) cin >> it;
        reverse(a[i].begin(), a[i].end());
    }
    int res = 0;
    // cout << gao() << endl;
    while (1) {
        if (!gao())
            break;
        ++res;
    }
    if (not done())
        res = -1;
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
