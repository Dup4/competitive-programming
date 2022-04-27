#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n"
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 998244353;
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
const int N = 2e5 + 10;
const ll INF = 1e18;
ll D;
int n, q;

mt19937 rnd(time(0));
inline ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
inline ll mul(ll a, ll b, ll p) {
    return (a * b - (ll)(a / (long double)p * b + 1e-3) * p + p) % p;
}
inline ll qmod(ll base, ll n, ll p) {
    ll res = 1;
    base %= p;
    while (n) {
        if (n & 1) {
            res = mul(res, base, p);
        }
        base = mul(base, base, p);
        n >>= 1;
    }
    return res;
}

map<ll, int> id;

struct Mill {
    ll n, fac[N][2], bk[N];
    int tot;
    const int C = 2307;
    const int S = 8;
    inline bool check(ll a, ll n) {
        ll m = n - 1, x, y = 0;
        int j = 0;
        while (!(m & 1)) {
            m >>= 1;
            ++j;
        }
        x = qmod(a, m, n);
        for (int i = 1; i <= j; x = y, ++i) {
            y = mul(x, x, n);
            if (y == 1 && x != 1 && x != n - 1) {
                return 1;
            }
        }
        return y != 1;
    }
    inline bool miller_rabin(ll n) {
        if (n < 2) {
            return 0;
        } else if (n == 2) {
            return 1;

        } else if (!(n & 1)) {
            return 0;
        }
        for (int i = 0; i < S; ++i) {
            if (check(rnd() % (n - 1) + 1, n)) {
                return 0;
            }
        }
        return 1;
    }
    inline ll pollard_rho(ll n, int c) {
        ll i = 1, k = 2, x = rnd() % n, y = x, d;
        while (1) {
            ++i;
            x = (mul(x, x, n) + c) % n;
            d = gcd(y - x, n);
            if (d > 1 && d < n) {
                return d;
            }
            if (y == x) {
                return n;
            }
            if (i == k) {
                y = x;
                k <<= 1;
            }
        }
    }
    inline void findfac(ll n, int c) {
        if (n == 1) {
            return;
        }
        if (miller_rabin(n)) {
            bk[++*bk] = n;
            return;
        }
        ll m = n;
        while (m == n) {
            m = pollard_rho(n, c--);
        }
        findfac(m, c);
        findfac(n / m, c);
    }
    inline void gao(ll _n, vector<ll> &vec) {
        vec.clear();
        if (_n == 1) {
            vec.push_back(1);
            return;
        }
        n = _n;
        *bk = 0;
        findfac(n, C);
        sort(bk + 1, bk + 1 + *bk);
        fac[1][0] = bk[1];
        fac[1][1] = 1;
        tot = 1;
        for (int i = 2; i <= *bk; ++i) {
            if (bk[i] == bk[i - 1]) {
                ++fac[tot][1];
            } else {
                ++tot;
                fac[tot][0] = bk[i];
                fac[tot][1] = 1;
            }
        }
        vec.push_back(1);
        for (int i = 1, sze = 0; i <= *bk; ++i) {
            if (i == 1 || bk[i - 1] % bk[i]) {
                sze = vec.size();
            } else {
                bk[i] *= bk[i - 1];
            }
            for (int j = 0; j < sze; ++j) {
                vec.push_back(bk[i] * vec[j]);
            }
        }
        sort(vec.begin(), vec.end());
    }
} mill;

struct Graph {
    struct E {
        int to, nx, w;
    } e[N << 1];
    int h[N], cnt;
    void init(int n) {
        for (int i = 0; i <= n; ++i) h[i] = -1;
        cnt = -1;
    }
    void addedge(int u, int v, int w = 0) {
        e[++cnt] = {v, h[u], w};
        h[u] = cnt;
    }
} G;

struct Dijkstra {
    struct node {
        int u;
        ll w;
        node(int u = 0, ll w = 0) : u(u), w(w) {}
        bool operator<(const node &other) const {
            return w > other.w;
        }
    };
    ll dis[N];
    int f[N];
    bool used[N];
    int gao(int s, int ed) {
        for (int i = 1; i <= n; ++i) {
            dis[i] = INF;
            used[i] = 0;
            f[i] = 0;
        }
        priority_queue<node> pq;
        dis[s] = 0;
        f[s] = 1;
        pq.push(node(s, dis[s]));
        while (!pq.empty()) {
            int u = pq.top().u;
            pq.pop();
            if (u == ed)
                return f[u];
            if (used[u])
                continue;
            used[u] = 1;
            for (int i = G.h[u]; ~i; i = G.e[i].nx) {
                int v = G.e[i].to, w = G.e[i].w;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    f[v] = f[u];
                    pq.push(node(v, dis[v]));
                } else if (dis[v] == dis[u] + w) {
                    chadd(f[v], f[u]);
                }
            }
        }
        assert(0);
    }
} dij;

ll fid[N];

__int128 one = 1;

void run() {
    rd(D);
    vector<ll> fac;
    mill.gao(D, fac);
    n = 0;
    for (auto &it : fac) id[it] = ++n, fid[n] = it;
    // dbg(n);
    G.init(n);
    int _n = mill.tot;
    ll bk[220];
    for (int i = 1; i <= _n; ++i) {
        bk[i] = mill.fac[i][0];
        //		dbg(i, bk[i]);
    }
    for (int i = 1; i <= n; ++i) {
        //	dbg(i, fid[i]);
        for (int j = 1; j <= _n; ++j) {
            //		dbg(j, bk[j]);
            //		dbg(fid[i], fid[i] * bk[j]);
            if (one * fid[i] * bk[j] <= D && D % (fid[i] * bk[j]) == 0) {
                int u = i, v = id[fid[i] * bk[j]];
                ll tmp = fid[i];
                while (tmp % bk[j] == 0) tmp /= bk[j];
                int cnt = 1;
                for (int k = 1; k <= _n; ++k) {
                    int now = 0;
                    while (tmp % bk[k] == 0) {
                        ++now;
                        tmp /= bk[k];
                    }
                    cnt *= (now + 1);
                }
                // dbg(u, v);
                G.addedge(u, v, cnt);
                G.addedge(v, u, cnt);
            }
        }
    }
    rd(q);
    while (q--) {
        ll u, v;
        rd(u, v);
        if (u == v)
            pt(1);
        else
            pt(dij.gao(id[u], id[v]));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
