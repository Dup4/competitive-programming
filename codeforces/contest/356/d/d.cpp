#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) ((int)x.size())
#define endl "\n"
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y, int Mod = mod) {
    x += y;
    while (x >= Mod) x -= Mod;
    while (x < 0) x += Mod;
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
inline ll qpow(ll base, ll n) {
    assert(n >= 0);
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
constexpr int N = 7e4 + 10;
int n, s, a[N], pos[N], used[N], son[N];
bitset<N> f, g, h;
void run() {
    int Max = 0, posMax = -1;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] > Max) {
            Max = a[i];
            posMax = i;
        }
    }
    if (Max > s)
        return pt(-1);
    memset(used, 0, sizeof used);
    memset(pos, -1, sizeof pos);
    f.reset();
    g.reset();
    f[0] = 1;
    g[0] = 1;
    pos[0] = 0;
    for (int i = 1; i <= n; ++i)
        if (i != posMax) {
            f = f | (f << a[i]);
            h = f;
            h &= (~g);
            for (int j = h._Find_first(); j != N; j = h._Find_next(j)) {
                pos[j] = i;
            }
            g = f;
        }
    if (pos[s - Max] == -1)
        return pt(-1);
    vector<int> vec;
    vec.push_back(posMax);
    used[posMax] = 1;
    int it = s - Max;
    while (it) {
        used[pos[it]] = 1;
        vec.push_back(pos[it]);
        it -= a[pos[it]];
    }
    vector<int> other;
    for (int i = 1; i <= n; ++i)
        if (!used[i])
            other.push_back(i);
    other.push_back(posMax);
    sort(other.begin(), other.end(), [&](int x, int y) {
        return a[x] < a[y];
    });
    memset(son, -1, sizeof son);
    for (int i = 1; i < SZ(other); ++i) {
        son[other[i]] = other[i - 1];
    }
    for (int i = 1; i <= n; ++i) {
        if (son[i] == -1) {
            pt(a[i], 0);
        } else {
            pt(a[i] - a[son[i]], 1, son[i]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> s) run();
    return 0;
}
