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
int n, q, a[N];
ll S[N];

struct BIT_2D {
    int mod;
    struct BIT {
        int n, mod;
        vector<int> a;
        void init(int _n, int _mod) {
            n = _n;
            mod = _mod;
            a.resize(n + 5);
        }
        void add(int x, int v) {
            for (; x <= n; chadd(a[x], v, mod), x += x & -x)
                ;
        }
        int ask(int x) {
            int res = 0;
            for (; x > 0; chadd(res, a[x], mod), x -= x & -x)
                ;
            return res;
        }
    } bit1, bit2;
    void init(int n, int mod) {
        this->mod = mod;
        bit1.init(n, mod);
        bit2.init(n, mod);
    }
    int ask(int x) {
        return (1ll * bit1.ask(x) * (x + 1) % mod - bit2.ask(x) + mod) % mod;
    }
    void add(int x, int v) {
        bit1.add(x, v);
        bit2.add(x, x * v % mod);
    }
    int ask(int l, int r) {
        return (ask(r) - ask(l - 1) + mod) % mod;
    }
    void add(int l, int r, int v) {
        add(l, v);
        add(r + 1, mod - v);
    }
};

struct E {
    int n, m;
    vector<BIT_2D> bit;
    void init(int _n, int _m) {
        m = _m;
        n = _n;
        for (int i = 0; i < m; ++i) {
            bit.push_back(BIT_2D());
            bit.back().init(n / m + 5, m);
        }
    }
    void add(int l, int r, int val, int d) {
        --l, --r;
        val %= m;
        d %= m;
        for (int i = 0, _l, _r; i < m; ++i) {
            _l = l / m;
            if (l % m < i)
                ++_l;
            _r = r / m;
            if (r % m >= i)
                ++_r;
            // assert(_l >= 0 && _r >= 0);
            bit[i].add(_l + 1, _r + 1, (d * i + val) % m);
        }
    }
    int ask(int l, int r) {
        --l, --r;
        int res = 0;
        for (int i = 0, _l, _r; i < m; ++i) {
            _l = l / m;
            if (l % m < i)
                ++_l;
            _r = r / m;
            if (r % m >= i)
                ++_r;
            // assert(_l >= 0 && _r >= 0);
            chadd(res, bit[i].ask(_l + 1, _r + 1));
        }
        return res;
    }
} e[10];

int id[110];

void run() {
    id[3] = 0;
    e[0].init(n, 3);
    id[5] = 1;
    e[1].init(n, 5);
    id[7] = 2;
    e[2].init(n, 7);
    id[11] = 3;
    e[3].init(n, 11);
    id[13] = 4;
    e[4].init(n, 13);
    id[17] = 5;
    e[5].init(n, 17);
    id[19] = 6;
    e[6].init(n, 19);
    id[23] = 7;
    e[7].init(n, 23);
    for (int i = 1; i <= n; ++i) {
        rd(a[i]);
        S[i] = S[i - 1] + a[i];
    }
    rd(q);
    for (int i = 1, op, l, r, val, d, m; i <= q; ++i) {
        rd(op, l, r);
        if (op == 1) {
            rd(val, d);
            for (int j = 0; j < 8; ++j) {
                e[j].add(l, r, val, d);
            }
        } else {
            rd(m);
            //	assert(m == 3);
            ll res = (S[r] - S[l - 1]) % m + e[id[m]].ask(l, r);
            pt(res % m);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}
