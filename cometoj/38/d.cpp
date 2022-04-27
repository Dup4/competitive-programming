#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, q, a[N];

struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) {
            a[x] ^= v;
        }
    }
    int query(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) {
            res ^= a[x];
        }
        return res;
    }
} bit;

struct SEG {
    struct node {
        int d[32];
        node() {
            memset(d, 0, sizeof d);
        }
        void insert(int x) {
            for (int i = 31; i >= 0; --i) {
                if ((x >> i) & 1) {
                    if (!d[i]) {
                        d[i] = x;
                        break;
                    } else {
                        x ^= d[i];
                    }
                }
            }
        }
        node operator+(const node &other) const {
            node res = *this;
            for (int i = 31; i >= 0; --i) {
                if (other.d[i]) {
                    res.insert(other.d[i]);
                }
            }
            return res;
        }
        //查询张成中与v异或后的最大的数
        int Max(int v) {
            int res = v;
            for (int i = 31; i >= 0; --i) {
                if ((res ^ d[i]) > res) {
                    res = res ^ d[i];
                }
            }
            return res;
        }
    } t[N << 2], res;
    void build(int id, int l, int r) {
        if (l == r) {
            t[id] = node();
            t[id].insert(a[l]);
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update(int id, int l, int r, int pos) {
        if (l == r) {
            t[id] = node();
            t[id].insert(a[l]);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos);
        else
            update(id << 1 | 1, mid + 1, r, pos);
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
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        bit.init();
        for (int i = n; i >= 1; --i) a[i] ^= a[i - 1], bit.update(i, a[i]);
        seg.build(1, 1, n);
        int op, l, r, v;
        while (q--) {
            scanf("%d%d%d%d", &op, &l, &r, &v);
            if (op == 1) {
                a[l] ^= v;
                seg.update(1, 1, n, l);
                bit.update(l, v);
                if (r < n) {
                    a[r + 1] ^= v;
                    seg.update(1, 1, n, r + 1);
                    bit.update(r + 1, v);
                }
            } else {
                seg.res = SEG::node();
                if (l + 1 <= r) {
                    seg.query(1, 1, n, l + 1, r);
                }
                //插入a[l]这个数
                seg.res.insert(bit.query(l));
                printf("%d\n", seg.res.Max(v));
            }
        }
    }
    return 0;
}
