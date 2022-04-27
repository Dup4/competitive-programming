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
int n;
vector<pII> res;
struct E {
    int x[3], id;
    E() {}
};
void gao(vector<E> &vec, int p) {
    if (vec.size() == 1)
        return;
    sort(vec.begin(), vec.end(), [&](E a, E b) {
        return a.x[p] < b.x[p];
    });
    vector<vector<E>> now;
    for (auto &it : vec) {
        if (now.empty()) {
            vector<E> tmp;
            tmp.push_back(it);
            now.push_back(tmp);
        } else {
            if (it.x[p] == now.back().back().x[p]) {
                now.back().push_back(it);
            } else {
                vector<E> tmp;
                tmp.push_back(it);
                now.push_back(tmp);
            }
        }
    }
    for (auto &it : now) gao(it, p + 1);
    vec.clear();
    for (auto &it : now) {
        if (!it.empty()) {
            assert(it.size() == 1);
            vec.push_back(it.back());
        }
    }
    while (vec.size() >= 2) {
        E u = vec.back();
        vec.pop_back();
        E v = vec.back();
        vec.pop_back();
        res.emplace_back(u.id, v.id);
    }
}
void run() {
    vector<E> e(n);
    for (int i = 0; i < n; ++i) {
        cin >> e[i].x[0] >> e[i].x[1] >> e[i].x[2];
        e[i].id = i + 1;
    }
    res.clear();
    gao(e, 0);
    for (auto &it : res) pt(it.fi, it.se);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
