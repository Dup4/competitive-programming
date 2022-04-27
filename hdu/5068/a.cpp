#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 50010
const ll p = 1e9 + 7;
int n, q;
void add(ll &x, ll y) {
    x += y;
    if (x >= p)
        x -= p;
}

struct SEG {
    struct node {
        ll a[2][2];
        node() {
            memset(a, 0, sizeof a);
        }
        node operator*(const node &other) const {
            node res = node();
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    for (int k = 0; k < 2; ++k) {
                        add(res.a[i][j], a[i][k] * other.a[k][j] % p);
                    }
                }
            }
            return res;
        }
    } t[N << 2], res;
    void build(int id, int l, int r) {
        if (l == r) {
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    t[id].a[i][j] = 1;
                }
            }
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] * t[id << 1 | 1];
    }
    void update(int id, int l, int r, int pos, int x, int y) {
        if (l == r) {
            t[id].a[x - 1][y - 1] ^= 1;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, x, y);
        else
            update(id << 1 | 1, mid + 1, r, pos, x, y);
        t[id] = t[id << 1] * t[id << 1 | 1];
    }
    node query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            return t[id];
        }
        int mid = (l + r) >> 1;
        if (ql <= mid && qr > mid) {
            return query(id << 1, l, mid, ql, qr) * query(id << 1 | 1, mid + 1, r, ql, qr);
        } else if (ql <= mid) {
            return query(id << 1, l, mid, ql, qr);
        } else if (qr > mid) {
            return query(id << 1 | 1, mid + 1, r, ql, qr);
        } else {
            assert(0);
        }
    }
} seg;

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        seg.build(1, 1, n);
        int op, x, y, z;
        ll res;
        while (q--) {
            scanf("%d%d%d", &op, &x, &y);
            switch (op) {
                case 0:
                    seg.res = seg.query(1, 1, n, x, y - 1);
                    res = 0;
                    for (int i = 0; i < 2; ++i) {
                        for (int j = 0; j < 2; ++j) {
                            add(res, seg.res.a[i][j]);
                        }
                    }
                    printf("%lld\n", res);
                    break;
                case 1:
                    scanf("%d", &z);
                    seg.update(1, 1, n, x, y, z);
                    break;
            }
        }
    }
    return 0;
}
