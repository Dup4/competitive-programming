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
constexpr int N = 2e5 + 10, INF = 0x3f3f3f3f;
int n, m;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
    void print() {
        pt(x, y);
    }
    bool operator<(const Point &other) const {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
};

struct SEG {
    struct node {
        int Max;
        set<int> s;
        void init() {
            Max = 0;
            s.clear();
        }
        node operator+(const node &other) const {
            node res;
            res.Max = max(Max, other.Max);
            return res;
        }
    } t[N << 2];
    Point res;
    void build(int id, int l, int r) {
        t[id].init();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int x, int y, int opt) {
        if (l == r) {
            if (opt == 0)
                t[id].s.insert(y);
            else
                t[id].s.erase(y);
            t[id].Max = 0;
            if (!t[id].s.empty())
                chmax(t[id].Max, *t[id].s.rbegin());
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(id << 1, l, mid, x, y, opt);
        else if (x > mid)
            update(id << 1 | 1, mid + 1, r, x, y, opt);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void query(int id, int l, int r, int qx, int qy) {
        if (res.x != INF || qx >= r || t[id].Max <= qy)
            return;
        if (l == r) {
            auto pos = t[id].s.upper_bound(qy);
            res = min(res, Point(l, *pos));
            return;
        }
        int mid = (l + r) >> 1;
        if (qx < mid)
            query(id << 1, l, mid, qx, qy);
        query(id << 1 | 1, mid + 1, r, qx, qy);
    }
} seg;

struct Hash {
    vector<int> a;
    int &operator[](int x) {
        return a[x - 1];
    }
    void init() {
        a.clear();
    }
    void add(int x) {
        a.push_back(x);
    }
    void gao() {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }
    int query(int x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
} hx, hy;

struct E {
    int op, x, y;
} e[N];

void run() {
    hx.init();
    hy.init();
    for (int i = 1; i <= n; ++i) {
        static string op;
        rd(op, e[i].x, e[i].y);
        hx.add(e[i].x);
        hy.add(e[i].y);
        if (op == "add")
            e[i].op = 0;
        else if (op == "remove")
            e[i].op = 1;
        else
            e[i].op = 2;
    }
    hx.gao();
    hy.gao();
    for (int i = 1; i <= n; ++i) {
        e[i].x = hx.query(e[i].x);
        e[i].y = hy.query(e[i].y);
    }
    m = hx.a.size();
    seg.build(1, 1, m);
    for (int i = 1; i <= n; ++i) {
        if (e[i].op <= 1) {
            seg.update(1, 1, m, e[i].x, e[i].y, e[i].op);
        } else {
            seg.res = Point(INF, INF);
            seg.query(1, 1, m, e[i].x, e[i].y);
            if (seg.res.x == INF)
                pt(-1);
            else
                pt(hx[seg.res.x], hy[seg.res.y]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
