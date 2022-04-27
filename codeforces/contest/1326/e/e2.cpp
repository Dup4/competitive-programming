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
constexpr int N = 3e5 + 10, INF = 0x3f3f3f3f;
int n, p[N], fp[N], q[N], del[N];

struct SEG {
    struct node {
        int Min, pos;
        node(int Min = 0, int pos = 0) : Min(Min), pos(pos) {}
        node operator+(const node &other) const {
            node res = node();
            if (Min < other.Min) {
                res = *this;
            } else {
                res = other;
            }
            return res;
        }
    } t[N << 2], res;
    void build(int id, int l, int r) {
        if (l == r) {
            t[id] = node(INF, l);
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update(int id, int l, int r, int pos, int v) {
        if (l == r) {
            t[id].Min = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, v);
        else
            update(id << 1 | 1, mid + 1, r, pos, v);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            res = res + t[id];
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            query(id << 1 | 1, mid + 1, r, ql, qr);
    }
} seg;

struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) a[x] += v;
    }
    int query(int x) {
        int res = 0;
        for (; x; x -= x & -x) res += a[x];
        return res;
    }
    int query(int l, int r) {
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
} bit;

void run() {
    for (int i = 1; i <= n; ++i) rd(p[i]), fp[p[i]] = i;
    for (int i = 1; i <= n; ++i) rd(q[i]);
    seg.build(1, 1, n);
    bit.init();
    priority_queue<int> pq;
    for (int i = 1; i <= n; ++i) {
        pq.emplace(p[i]);
        if (i != q[n]) {
            bit.update(i, 1);
            int top = pq.top();
            pq.pop();
            //	dbg(fp[top], top);
            seg.update(1, 1, n, fp[top], top);
        }
    }
    int res = pq.top();
    del[fp[res]] = 1;
    vector<int> vec;
    vec.push_back(res);
    for (int i = n - 1; i >= 1; --i) {
        if (del[q[i]] == 0 && bit.query(q[i] + 1, n) == 0) {
            chmax(res, p[q[i]]);
            seg.update(1, 1, n, q[i], INF);
            del[q[i]] = 1;
        } else {
            seg.res = SEG::node(INF, 0);
            seg.query(1, 1, n, 1, q[i]);
            // dbg(i, seg.res.Min, seg.res.pos);
            if (seg.res.Min != INF) {
                del[seg.res.pos] = 1;
                chmax(res, seg.res.Min);
                seg.update(1, 1, n, seg.res.pos, INF);
            }
        }
        bit.update(q[i], -1);
        vec.push_back(res);
    }
    reverse(vec.begin(), vec.end());
    for (int i = 0; i < n; ++i) cout << vec[i] << " \n"[i == n - 1];
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
