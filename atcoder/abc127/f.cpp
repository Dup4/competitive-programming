#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n, q;
int bb[N];
struct qnode {
    int op, a, b;
    void scan() {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &a, &b);
            bb[++n] = a;
        }
    }
} qrr[N];
void Hash() {
    sort(bb + 1, bb + 1 + n);
    n = unique(bb + 1, bb + 1 + n) - bb - 1;
}
int getid(int x) {
    return lower_bound(bb + 1, bb + 1 + n, x) - bb;
}
struct BIT {
    ll a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, ll val) {
        for (; x < N; x += x & -x) {
            a[x] += val;
        }
    }
    ll query(int x) {
        ll res = 0;
        for (; x > 0; x -= x & -x) {
            res += a[x];
        }
        return res;
    }
    ll query(int l, int r) {
        return query(r) - query(l - 1);
    }
} bit;
struct SEG {
    int sum[N << 2];
    void init() {
        memset(sum, 0, sizeof sum);
    }
    void update(int id, int l, int r, int pos) {
        if (l == r) {
            ++sum[id];
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos);
        else
            update(id << 1 | 1, mid + 1, r, pos);
        sum[id] = sum[id << 1] + sum[id << 1 | 1];
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (ql > qr) {
            return 0;
        }
        if (l >= ql && r <= qr) {
            return sum[id];
        }
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid)
            res += query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            res += query(id << 1 | 1, mid + 1, r, ql, qr);
        return res;
    }
    int query(int id, int l, int r, int k) {
        if (l == r) {
            return l;
        }
        int mid = (l + r) >> 1;
        if (k <= sum[id << 1]) {
            return query(id << 1, l, mid, k);
        } else {
            return query(id << 1 | 1, mid + 1, r, k - sum[id << 1]);
        }
    }
} seg;

int main() {
    while (scanf("%d", &q) != EOF) {
        n = 0;
        for (int i = 1; i <= q; ++i) {
            qrr[i].scan();
        }
        Hash();
        bit.init();
        seg.init();
        int tot = 0, mid, id;
        ll lazy = 0;
        for (int i = 1; i <= q; ++i) {
            switch (qrr[i].op) {
                case 1:
                    ++tot;
                    lazy += qrr[i].b;
                    id = getid(qrr[i].a);
                    seg.update(1, 1, n, id);
                    bit.update(id, qrr[i].a);
                    break;
                case 2:
                    mid = (tot + 1) / 2;
                    id = seg.query(1, 1, n, mid);
                    printf("%d %lld\n", bb[id],
                            lazy + 1ll * (seg.query(1, 1, n, 1, id - 1) - seg.query(1, 1, n, id + 1, n)) * bb[id] +
                                    bit.query(id + 1, n) - bit.query(1, id - 1));
                    break;
                default:
                    assert(0);
            }
        }
    }
    return 0;
}
