#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, q, a[N];

struct SEG {
    const static ll INF = 0x3f3f3f3f3f3f3f3f;
    struct TAG {
        ll a, b;
        TAG() {}
        TAG(ll a, ll b) : a(a), b(b) {}
        void init() {
            a = 0, b = -INF;
        }
        TAG operator+(const TAG &other) {
            return {max(-INF, a + other.a), max(b + other.a, other.b)};
        }
        TAG operator*(const TAG &other) {
            return {max(a, other.a), max(b, other.b)};
        }
        ll calc(ll x) {
            return max(x + a, b);
        }
    };
    struct node {
        ll v, hv;
        TAG lazy, hlazy;
        node() {}
        void init() {
            v = hv = -INF;
            lazy.init();
            hlazy.init();
        }
        void up(TAG _lazy, TAG _hlazy) {
            hlazy = hlazy * (lazy + _hlazy);
            lazy = lazy + _lazy;
            hv = max(hv, _hlazy.calc(v));
            v = _lazy.calc(v);
        }
        node operator+(const node &other) const {
            node res;
            res.init();
            res.v = max(v, other.v);
            res.hv = max(hv, other.hv);
            return res;
        }
    } t[N << 2], res;
    void pushdown(int id) {
        TAG &lazy = t[id].lazy, &hlazy = t[id].hlazy;
        t[id << 1].up(lazy, hlazy);
        t[id << 1 | 1].up(lazy, hlazy);
        lazy.init();
        hlazy.init();
    }
    void build(int id, int l, int r) {
        t[id].init();
        if (l == r) {
            t[id].v = t[id].hv = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update(int id, int l, int r, int ql, int qr, TAG v) {
        if (l >= ql && r <= qr) {
            t[id].up(v, v);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
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
        pushdown(id);
        if (ql <= mid)
            query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            query(id << 1 | 1, mid + 1, r, ql, qr);
    }
} seg;

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        seg.build(1, 1, n);
        scanf("%d", &q);
        char op[10];
        for (int _q = 1, x, y, z; _q <= q; ++_q) {
            scanf("%s%d%d", op, &x, &y);
            if (op[0] == 'Q') {
                seg.res.init();
                seg.query(1, 1, n, x, y);
                printf("%lld\n", seg.res.v);
            } else if (op[0] == 'A') {
                seg.res.init();
                seg.query(1, 1, n, x, y);
                printf("%lld\n", seg.res.hv);
            } else if (op[0] == 'P') {
                scanf("%d", &z);
                seg.update(1, 1, n, x, y, SEG::TAG(z, -SEG::INF));
            } else if (op[0] == 'C') {
                scanf("%d", &z);
                seg.update(1, 1, n, x, y, SEG::TAG(-SEG::INF, z));
            }
        }
    }
    return 0;
}
