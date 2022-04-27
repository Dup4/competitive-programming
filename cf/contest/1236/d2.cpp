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
inline void pt() {
    cout << endl;
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    pt(args...);
}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
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
constexpr int N = 1e5 + 10;
int n, m, k;
set<int> row[N], col[N];
bool del(int up, int down, int left, int right) {
    for (int i = up; i <= down; ++i) {
        for (int j = left; j <= right; ++j) {
            if (row[i].find(j) == row[i].end() || col[j].find(i) == col[j].end()) {
                return false;
            } else {
                row[i].erase(j);
                col[j].erase(i);
                --k;
            }
        }
    }
    return true;
}
// dir
// 0 right
// 1 down
// 2 left
// 3 up
void run() {
    for (int i = 1; i <= n; ++i) row[i].clear();
    for (int i = 1; i <= m; ++i) col[i].clear();
    for (int i = 1, x, y; i <= k; ++i) {
        cin >> x >> y;
        row[x].insert(y);
        col[y].insert(x);
    }
    if (!k)
        return pt("Yes");
    int up = 1, down = n, left = 1, right = m;
    int x = 1, y = 1, dir = 0;
    bool F = 0;
    while (k) {
        //	dbg(up, down, left, right, dir, x, y);
        if (dir == 0) {  // right
            auto it = row[x].begin();
            if (it == row[x].end()) {
                y = right;
            } else {
                int pos = *it;
                if (!del(up, down, pos, right)) {
                    return pt("No");
                }
                right = pos - 1;
                y = pos - 1;
            }
            left += F;
        } else if (dir == 1) {  // down
            auto it = col[y].begin();
            if (it == col[y].end()) {
                x = down;
            } else {
                int pos = *it;
                if (!del(pos, down, left, right)) {
                    return pt("No");
                }
                down = pos - 1;
                x = pos - 1;
            }
            up += F;
        } else if (dir == 2) {  // left
            auto it = row[x].end();
            if (it != row[x].begin()) {
                --it;
                int pos = *it;
                if (!del(up, down, left, pos)) {
                    return pt("No");
                }
                left = pos + 1;
                y = pos + 1;
            } else {
                y = left;
            }
            right -= F;
        } else {  // up
            auto it = col[y].end();
            if (it != col[y].begin()) {
                --it;
                int pos = *it;
                if (!del(up, pos, left, right)) {
                    return pt("No");
                }
                up = pos + 1;
                x = pos + 1;
            } else {
                x = up;
            }
            down -= F;
        }
        dir = (dir + 1) % 4;
        F = 1;
    }
    pt("Yes");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m >> k) run();
    return 0;
}
