#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
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
#define fi first
#define se second
const int mod = 998244353;
const int N = 1e6 + 10;
int n, a[N];
struct E {
    int p, l, r, g;
};
vector<vector<E>> vec;
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

void init() {
    vector<E> pre, now;
    for (int i = 1; i <= n; ++i) {
        now.clear();
        pre.push_back({i, i, i, a[i]});
        for (auto &it : pre) {
            if (now.empty()) {
                now.push_back({i, it.l, it.r, gcd(it.g, a[i])});
            } else {
                int g = gcd(it.g, a[i]);
                if (g == now.back().g) {
                    now.back().r = it.r;
                } else {
                    now.push_back({i, it.l, it.r, g});
                }
            }
        }
        for (auto &it : now) {
            vec[it.g].push_back(it);
        }
        pre = now;
    }
}

struct SEG {
    struct node {
        pII v, lazy;
        int cnt;
        node() {
            v = pII(0, 0);
            lazy = pII(-1, -1);
        }
        void up(pII _lazy) {
            v.fi = _lazy.fi;
            v.se = 1ll * _lazy.se * cnt % mod;
            lazy = _lazy;
        }
        node operator+(const node &other) const {
            node res = node();
            res.cnt = cnt + other.cnt;
            if (v.fi > other.v.fi) {
                res.v = v;
            } else if (v.fi < other.v.fi) {
                res.v = other.v;
            } else {
                res.v = v;
                res.v.se += other.v.se;
                res.v.se %= mod;
            }
            return res;
        }
    } t[N << 2], res;
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            t[id].cnt = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void down(int id) {
        pII &lazy = t[id].lazy;
        if (lazy == pII(-1, -1))
            return;
        t[id << 1].up(lazy);
        t[id << 1 | 1].up(lazy);
        lazy = pII(-1, -1);
    }
    void update(int id, int l, int r, int ql, int qr, pII v) {
        if (ql > qr)
            return;
        if (l >= ql && r <= qr) {
            t[id].up(v);
            //	dbg(v.fi, v.se, t[id].v.fi, t[id].v.se);
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

pII gao(int x) {
    if (vec[x].empty())
        return pII(0, 0);
    seg.update(1, 0, n, 0, n, pII(0, 1));
    pII pre = pII(0, 0), res = pII(0, 0);
    for (auto &it : vec[x]) {
        seg.res = SEG::node();
        seg.query(1, 0, n, it.l - 1, it.r - 1);
        ++seg.res.v.fi;
        pre = max(pre, seg.res.v);
        if (pre.fi > res.fi)
            res = pre;
        else {
            res.se += pre.se;
            res.se %= mod;
        }
        seg.update(1, 0, n, it.p, n, res);
    }
    return res;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        vec.clear();
        vec.resize(N);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        init();
        seg.build(1, 0, n);
        pII res = pII(0, 0);
        for (int i = 1; i <= 1000000; ++i) {
            pII tmp = gao(i);
            if (tmp.fi > res.fi) {
                res = tmp;
            } else if (tmp.fi == res.fi) {
                res.se += tmp.se;
                res.se %= mod;
            }
        }
        printf("%d %d\n", res.fi, res.se);
    }
    return 0;
}
