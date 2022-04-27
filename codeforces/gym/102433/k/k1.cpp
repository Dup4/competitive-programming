#include <bits/stdc++.h>
#define SZ(x) (int(x.size()))
#define fi first
#define se second
using namespace std;
using ll = long long;
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
const int N = 5e5 + 10;
int n, m, q, ver[N], sze[N], res[N], isQuery[N];
vector<vector<int>> vec;

struct W {
    int i, p, ver;
};

struct SEG {
    struct node {
        W val, lazy;
        void init() {
            val = lazy = {-1, -1, -1};
        }
        void up(W _lazy) {
            val = _lazy;
            lazy = _lazy;
        }
    } t[N << 2], res;
    void down(int id) {
        W &lazy = t[id].lazy;
        if (lazy.i == -1)
            return;
        t[id << 1].up(lazy);
        t[id << 1 | 1].up(lazy);
        lazy = {-1, -1, -1};
    }
    void build(int id, int l, int r) {
        t[id].init();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int ql, int qr, W v) {
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
    }
    W query(int id, int l, int r, int pos) {
        if (l == r)
            return t[id].val;
        int mid = (l + r) >> 1;
        down(id);
        if (pos <= mid)
            return query(id << 1, l, mid, pos);
        else
            return query(id << 1 | 1, mid + 1, r, pos);
    }
} seg;

struct TSEG {
    struct node {
        int lazy, sum;
        node() {
            lazy = sum = 0;
        }
        void up(int _lazy) {
            sum += _lazy;
            lazy += _lazy;
        }
        node operator+(const node &other) const {
            node res = node();
            res.sum = sum + other.sum;
            return res;
        }
    } t[N << 2];
    void down(int id) {
        int &lazy = t[id].lazy;
        t[id << 1].up(lazy);
        t[id << 1 | 1].up(lazy);
        lazy = 0;
    }
    void build(int id, int l, int r, const vector<int> &a) {
        if (l == r) {
            t[id].sum = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid, a);
        build(id << 1 | 1, mid + 1, r, a);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update(int id, int l, int r, int ql, int qr, int v) {
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
    }
    int query(int id, int l, int r, int pos) {
        if (l == r)
            return t[id].sum;
        int mid = (l + r) >> 1;
        down(id);
        if (pos <= mid)
            return query(id << 1, l, mid, pos);
        else
            return query(id << 1 | 1, mid + 1, r, pos);
    }
} tseg;

struct E {
    int l, r;
    vector<pII> vec;
};

vector<vector<E>> OP;

int main() {
    scanf("%d%d%d", &n, &m, &q);
    vec.resize(m + 1);
    OP.clear();
    OP.resize(m + 1);
    seg.build(1, 1, n);
    for (int i = 1, sz; i <= m; ++i) {
        scanf("%d", &sz);
        sze[i] = sz;
        ver[i] = 0;
        vector<int> tmp(sz + 1);
        for (int j = 1, x; j <= sz; ++j) {
            scanf("%d", &x);
            tmp[j] = x;
        }
        vec[i] = tmp;
        //	dbg(i, sz);
    }
    for (int _q = 1; _q <= q; ++_q) {
        isQuery[_q] = 0;
        int op, i, l, r, p;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &i, &p);
            seg.update(1, 1, n, p, p + sze[i] - 1, {i, p, ver[i]});
        } else if (op == 2) {
            scanf("%d", &p);
            isQuery[_q] = 1;
            W tmp = seg.query(1, 1, n, p);
            //	dbg(_q, tmp.i, tmp.p, tmp.ver);
            if (tmp.i == -1) {
                res[_q] = 0;
            } else if (tmp.ver == 0) {
                res[_q] = vec[tmp.i][p - tmp.p + 1];
            } else {
                //		dbg(_q);
                OP[tmp.i][tmp.ver - 1].vec.push_back(pII(_q, p - tmp.p + 1));
            }
        } else {
            scanf("%d%d%d", &i, &l, &r);
            ++ver[i];
            OP[i].push_back({l, r, {}});
        }
    }
    for (int i = 1; i <= m; ++i) {
        int _n = sze[i];
        tseg.build(1, 1, _n, vec[i]);
        for (auto &_it : OP[i]) {
            tseg.update(1, 1, _n, _it.l, _it.r, 1);
            for (auto &it : _it.vec) {
                res[it.fi] = tseg.query(1, 1, _n, it.se);
            }
        }
    }
    for (int i = 1; i <= q; ++i)
        if (isQuery[i])
            printf("%d\n", res[i] % 256);
    return 0;
}
