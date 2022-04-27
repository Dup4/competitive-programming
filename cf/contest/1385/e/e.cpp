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
constexpr int N = 2e5 + 10;
int n, m, in[N], out[N], _in[N], ord[N];

vector<vector<int>> G, T;
vector<pII> E;

bool ok() {
    queue<int> que;
    for (int i = 1; i <= n; ++i) {
        _in[i] = in[i];
        // dbg(i, _in[i]);
        if (_in[i] == 0) {
            que.push(i);
        }
    }
    int cnt = 0;
    while (!que.empty()) {
        ++cnt;
        int u = que.front();
        que.pop();
        ord[u] = cnt;
        for (auto &v : T[u]) {
            if (--_in[v] == 0)
                que.push(v);
        }
    }
    //	dbg(cnt);
    return cnt == n;
}

void run() {
    rd(n, m);
    E.clear();
    G.clear();
    G.resize(n + 1);
    memset(in, 0, sizeof(in[0]) * (n + 5));
    for (int i = 1, tp, u, v; i <= m; ++i) {
        rd(tp, u, v);
        if (tp == 0) {
            E.push_back(pII(min(u, v), max(u, v)));
        } else {
            G[u].push_back(v);
            ++out[u];
            ++in[v];
        }
    }
    //	shuffle(all(E), rnd);
    T = G;
    if (!ok())
        return pt("NO");
    T = G;
    for (auto &it : E) {
        int u = it.fi, v = it.se;
        if (ord[u] > ord[v])
            swap(u, v);
        T[u].push_back(v);
        ++out[u];
        ++in[v];
    }
    if (ok()) {
        pt("YES");
        for (int u = 1; u <= n; ++u)
            for (auto &v : T[u]) {
                pt(u, v);
            }
        return;
    }
    //	T = G;
    //	for (auto &it : E) {
    //		int u = it.fi, v = it.se;
    //		T[v].push_back(u);
    //		--out[u];
    //		++in[u];
    //		--in[v];
    //		++out[v];
    //	}
    //	if (ok()) {
    //		pt("YES");
    //		for (auto &it : E)
    //			pt(it.se, it.fi);
    //		return;
    //	}
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
