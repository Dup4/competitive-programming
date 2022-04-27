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
constexpr int N = 2e5 + 10, M = 20;
int n, d[N], fd[N];
pII a[N], b[N], c[N];

struct RMQ {
    pII Max[N][M];
    pII Min[N][M];
    int mm[N];
    void init(int n, pII *a, pII *b) {
        mm[0] = -1;
        for (int i = 1; i <= n; ++i) {
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
            Max[i][0] = a[i];
            Min[i][0] = b[i];
        }
        for (int j = 1; j <= mm[n]; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
                Min[i][j] = min(Min[i][j - 1], Min[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    pII queryMax(int x, int y) {
        int k = mm[y - x + 1];
        return max(Max[x][k], Max[y - (1 << k) + 1][k]);
    }
    pII queryMin(int x, int y) {
        int k = mm[y - x + 1];
        return min(Min[x][k], Min[y - (1 << k) + 1][k]);
    }
} rmq;

void out(int l, int r, int *a) {
    for (int i = l; i <= r; ++i) cout << a[i] << " \n"[i == r];
}

void print(int x, int y) {
    pt("NO");
    out(1, n, d);
    swap(d[x], d[y]);
    out(1, n, d);
}

void run() {
    rd(n);
    vector<vector<pII>> vec(n + 5);
    for (int i = 1; i <= n; ++i) {
        rd(a[i].fi, a[i].se);
        b[i] = pII(a[i].se, i);
        c[i] = pII(a[i].fi, i);
        vec[a[i].fi].push_back(pII(a[i].se, i));
    }
    priority_queue<pII, vector<pII>, greater<pII>> pq;
    for (int i = 1; i <= n; ++i) {
        for (auto &it : vec[i]) {
            pq.push(it);
        }
        pII top = pq.top();
        pq.pop();
        d[top.se] = i;
        fd[i] = top.se;
        b[i] = pII(a[top.se].se, top.se);
        c[i] = pII(a[top.se].fi, top.se);
    }
    rmq.init(n, b, c);
    for (int i = 1; i <= n; ++i) {
        int x = fd[i];
        if (a[x].fi < i) {
            pII it = rmq.queryMax(a[x].fi, i - 1);
            if (it.fi >= i) {
                return print(x, it.se);
            }
        }
        if (a[x].se > i) {
            pII it = rmq.queryMin(i + 1, a[x].se);
            if (it.fi <= i) {
                return print(x, it.se);
            }
        }
    }
    pt("YES");
    for (int i = 1; i <= n; ++i) cout << d[i] << " \n"[i == n];
}

int main() {
    //	priority_queue <int, vector<int>, greater<int>> pq;
    //	pq.push(1);
    //	pq.push(2);
    //	cout << pq.top() <<endl;
    //	return 0;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    //	int _T = nextInt();
    //	while (_T--) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    run();
    return 0;
}
