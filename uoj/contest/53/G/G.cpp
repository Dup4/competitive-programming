#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
#define endl "\n"
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
inline int nextInt() {
    int x;
    cin >> x;
    return x;
}
void rd() {}
template <class T, class... Ts>
void rd(T &arg, Ts &...args) {
    cin >> arg;
    rd(args...);
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
constexpr int N = 1e5 + 10;
int n;

vector<int> X, Y;

inline bool sqr(int x) {
    return x * x;
}

int dis(int i, int j) {
    return sqr(X[i] - X[j]) + sqr(Y[i] - Y[j]);
}

pII slop(int i, int j) {
    return pII(Y[i] - Y[j], X[i] - X[j]);
}

bool ok() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            if (j != i) {
                for (int k = 0; k < n; ++k)
                    if (k != j && k != i) {
                        for (int o = 0; o < n; ++o)
                            if (o != k) {
                                // if (o != j && o != i && o != k) {
                                int _dis = dis(i, j), __dis = dis(k, o);
                                pII _slop = slop(i, j), __slop = slop(k, o);
                                if (_dis == __dis && _slop.fi * __slop.se == _slop.se * __slop.fi) {
                                    return false;
                                }
                            }
                    }
            }
    }
    return true;
}

void run() {
    rd(n);
    X.clear();
    for (int i = 1; i <= n; ++i) X.push_back(i);
    do {
        Y.clear();
        for (int i = 1; i <= n; ++i) Y.push_back(i);
        do {
            if (ok()) {
                for (int i = 0; i < n; ++i) pt(X[i], Y[i]);
                pt("----------");
                return;
            }
        } while (next_permutation(all(Y)));
        break;
    } while (1);
    // next_permutation(all(X)));
    pt("NO");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    while (_T--) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}
