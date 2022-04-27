#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
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

inline ll sqr(ll x) {
    return x * x;
}
inline ll dis(pLL a, pLL b) {
    return sqr(a.fi - b.fi) + sqr(a.se - b.se);
}

ll closePair(vector<pLL> &A, int l, int r) {
    if (r - l <= 5) {
        ll ans = 1e18;
        for (int i = l; i <= r; ++i)
            for (int j = i + 1; j <= r; ++j) chmin(ans, dis(A[i], A[j]));
        return ans;
    }
    int mid = (l + r) >> 1;
    ll ans = min(closePair(A, l, mid), closePair(A, mid + 1, r));
    vector<pLL> B;
    for (int i = l; i <= r; ++i) {
        if (sqr(A[mid].fi - A[i].fi) <= ans)
            B.push_back(A[i]);
    }
    sort(B.begin(), B.end(), [&](pLL k1, pLL k2) {
        return k1.se < k2.se;
    });
    for (int i = 0; i < SZ(B); ++i)
        for (int j = i + 1; j < SZ(B) && sqr(B[j].se - B[i].se) < ans; ++j) chmin(ans, dis(B[i], B[j]));
    return ans;
}

void run() {
    vector<pLL> a(n);
    for (int i = 0; i < n; ++i) {
        rd(a[i].fi);
        a[i].se = a[i - 1].se + a[i].fi;
        a[i].fi = i;
    }
    sort(a.begin(), a.end());
    pt(closePair(a, 0, SZ(a) - 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
