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
constexpr int N = 2e6 + 10;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, m;

struct Hash {
    vector<int> a;
    int &operator[](int x) {
        return a[x - 1];
    }
    int size() {
        return a.size();
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
    int get(int x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
} hs;

struct SEG {
    struct node {
        ll Max, lazy;
        int pos;
        node() {
            Max = -INFLL, lazy = 0;
            pos = 0;
        }
        void up(ll _lazy) {
            Max += _lazy;
            lazy += _lazy;
        }
        node operator+(const node &other) const {
            node res = node();
            if (Max > other.Max) {
                res.Max = Max;
                res.pos = pos;
            } else {
                res.Max = other.Max;
                res.pos = other.pos;
            }
            return res;
        }
    } t[N << 2], res;
    void down(int id) {
        ll &lazy = t[id].lazy;
        t[id << 1].up(lazy);
        t[id << 1 | 1].up(lazy);
        lazy = 0;
    }
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            t[id].Max = hs[l];
            t[id].pos = l;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update(int id, int l, int r, int ql, int qr, ll v) {
        if (ql > qr)
            return;
        if (l >= ql && r <= qr) {
            t[id].up(v);
            return;
        }
        int mid = (l + r) >> 1;
        down(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void query(int id, int l, int r, int ql, int qr) {
        if (ql > qr)
            return;
        if (l >= ql && r <= qr) {
            res = res + t[id];
            return;
        }
        int mid = (l + r) >> 1;
        down(id);
        if (ql <= mid)
            query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            query(id << 1 | 1, mid + 1, r, ql, qr);
    }
} seg;

struct E {
    int x, y, c;
    void scan() {
        rd(x, y, c);
        hs.add(x);
        hs.add(y);
    }
} e[N];

struct ANS {
    ll val;
    int x1, y1, x2, y2;
    bool operator<(const ANS &other) const {
        return val < other.val;
    }
};

void run() {
    hs.init();
    hs.add(0);
    for (int i = 1; i <= n; ++i) e[i].scan();
    hs.gao();
    int pos = 0;
    for (int i = 1; i <= hs.size(); ++i) {
        if (hs[i] == pos)
            ++pos;
        else
            break;
    }
    ANS ans = {0, pos, pos, pos, pos};
    m = hs.size();
    seg.build(1, 1, m);
    vector<vector<E>> vec(m + 1);
    for (int i = 1; i <= n; ++i) {
        e[i].x = hs.get(e[i].x);
        e[i].y = hs.get(e[i].y);
        vec[max(e[i].x, e[i].y)].push_back(e[i]);
    }
    for (int i = 1; i <= m; ++i) {
        ANS now = {-INFLL, 0, 0, hs[i], hs[i]};
        for (auto &it : vec[i]) {
            //		dbg(i, it.x, it.y, min(it.x, it.y) + 1, -it.c);
            //	seg.update(1, 1, m, min(it.x, it.y) + 1, m, -it.c);
            seg.update(1, 1, m, 1, min(it.x, it.y), it.c);
        }
        seg.res = SEG::node();
        seg.query(1, 1, m, 1, i);
        now.val = -hs[i] + seg.res.Max;
        now.x1 = now.y1 = hs[seg.res.pos];
        //	dbg(i, now.val, now.x1, now.y1, now.x2, now.y2, seg.res.Max);
        ans = max(ans, now);
    }
    pt(ans.val);
    pt(ans.x1, ans.y1, ans.x2, ans.y2);
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
