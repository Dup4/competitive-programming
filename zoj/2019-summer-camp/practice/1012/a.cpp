#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = 998244353;
int n, q, a[N];
ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = res * base % p;
        }
        base = base * base % p;
        n >>= 1;
    }
    return res;
}
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
        void set() {
            memset(a, 0, sizeof a);
            a[0][0] = a[1][1] = 1;
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
    } t[N << 2], f, g;
    void build(int id, int l, int r) {
        if (l == r) {
            t[id] = node();
            t[id].a[0][0] = a[l];
            t[id].a[0][1] = t[id].a[1][0] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] * t[id << 1 | 1];
    }
    void update(int id, int l, int r, int pos) {
        if (l == r) {
            t[id].a[0][0] = a[pos];
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos);
        else
            update(id << 1 | 1, mid + 1, r, pos);
        t[id] = t[id << 1] * t[id << 1 | 1];
    }
    node query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr)
            return t[id];
        int mid = (l + r) >> 1;
        node tmp = node();
        tmp.set();
        if (ql <= mid)
            tmp = tmp * query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            tmp = tmp * query(id << 1 | 1, mid + 1, r, ql, qr);
        return tmp;
    }
} seg;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        seg.build(1, 1, n);
        scanf("%d", &q);
        int op, x, y;
        while (q--) {
            scanf("%d%d%d", &op, &x, &y);
            switch (op) {
                case 1:
                    a[x] = y;
                    seg.update(1, 1, n, x);
                    break;
                case 2:
                    if (x == y) {
                        printf("%d\n", a[x]);
                    } else {
                        seg.f = seg.query(1, 1, n, x, y);
                        seg.g = seg.query(1, 1, n, x + 1, y);
                        printf("%lld\n", seg.f.a[0][0] * qmod(seg.g.a[0][0], p - 2) % p);
                    }
                    break;
            }
        }
    }
    return 0;
}
