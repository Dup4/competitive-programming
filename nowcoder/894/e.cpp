#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
const ll p = 1e9 + 7;
int b[N], n;
ll sum[N];
struct qnode {
    int op, v, t, m;
    void scan() {
        scanf("%d%d%d", &op, &v, &t);
        if (op == 1) {
            scanf("%d", &m);
        }
        v -= 10 * t;
        b[++b[0]] = v;
    }
} qrr[N];

void Hash() {
    sort(b + 1, b + 1 + b[0]);
    b[0] = unique(b + 1, b + 1 + b[0]) - b - 1;
    n = b[0];
}
int id(int x) {
    return lower_bound(b + 1, b + 1 + n, x) - b;
}

struct SEG {
    struct node {
        ll base, sum[3];
        node() {
            base = sum[0] = sum[1] = sum[2] = 0;
        }
        node operator+(const node &other) const {
            node res = node();
            for (int i = 0; i < 3; ++i) {
                res.sum[i] = (sum[i] + other.sum[i]) % p;
            }
            return res;
        }
    } t[N << 2], res;
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            t[id].base = (b[l] + p) % p;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int pos, int x) {
        if (l == r) {
            (t[id].sum[0] += t[id].base * t[id].base % p * x % p) %= p;
            (t[id].sum[1] += t[id].base * x % p * 2 % p) %= p;
            (t[id].sum[2] += x) %= p;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, x);
        else
            update(id << 1 | 1, mid + 1, r, pos, x);
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

int main() {
    b[0] = 0;
    int Q;
    scanf("%d", &Q);
    for (int i = 1; i <= Q; ++i) {
        qrr[i].scan();
    }
    Hash();
    seg.build(1, 1, n);
    for (int i = 1; i <= Q; ++i) {
        if (qrr[i].op == 1) {
            seg.update(1, 1, n, id(qrr[i].v), qrr[i].m);
        } else {
            seg.res = SEG::node();
            seg.query(1, 1, n, 1, id(qrr[i].v));
            ll v = 1ll * qrr[i].t * 10;
            ll res = (seg.res.sum[0] + seg.res.sum[1] * v % p + seg.res.sum[2] * v % p * v % p) % p;
            // cout << seg.res.sum[0] << " " << seg.res.sum[1] << " " << seg.res.sum[2] << endl;
            printf("%lld\n", (res + p) % p);
        }
    }
    return 0;
}
