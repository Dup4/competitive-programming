#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
const ll p = 1e9 + 7;
int n, q, a[N], b[N], c[N], f[2];

void add(ll &x, ll y) {
    x += y;
    if (x >= p)
        x -= p;
}
struct SEG {
    struct node {
        ll a[4][4];
        node() {
            memset(a, 0, sizeof a);
        }
        void set() {
            memset(a, 0, sizeof a);
            for (int i = 0; i < 4; ++i) a[i][i] = 1;
        }
        node operator*(const node &other) const {
            node res = node();
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    for (int k = 0; k < 4; ++k) {
                        add(res.a[i][j], a[i][k] * other.a[k][j] % p);
                    }
                }
            }
            return res;
        }
    } t[N << 2], res;
    void build(int id, int l, int r) {
        if (l == r) {
            t[id].a[0][0] = t[id].a[0][3] = a[l];
            t[id].a[1][0] = t[id].a[1][3] = b[l];
            t[id].a[2][0] = t[id].a[2][3] = c[l];
            t[id].a[0][1] = t[id].a[2][2] = t[id].a[3][3] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] * t[id << 1 | 1];
    }
    void update(int id, int l, int r, int x) {
        if (l == r) {
            t[id].a[0][0] = t[id].a[0][3] = a[x];
            t[id].a[1][0] = t[id].a[1][3] = b[x];
            t[id].a[2][0] = t[id].a[2][3] = c[x];
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(id << 1, l, mid, x);
        else
            update(id << 1 | 1, mid + 1, r, x);
        t[id] = t[id << 1] * t[id << 1 | 1];
    }
    void query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            res = res * t[id];
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            query(id << 1 | 1, mid + 1, r, ql, qr);
    }
} seg;

ll get(int x) {
    if (x < 0)
        return 0;
    if (x <= 1) {
        ll res = 0;
        for (int i = 0; i <= x; ++i) {
            add(res, f[i]);
        }
        return res;
    } else {
        seg.res = SEG::node();
        seg.res.a[0][0] = f[1];
        seg.res.a[0][1] = f[0];
        seg.res.a[0][2] = 1;
        seg.res.a[0][3] = (f[0] + f[1]) % p;
        seg.query(1, 2, n - 1, 2, x);
        return seg.res.a[0][3];
    }
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        scanf("%d%d", f, f + 1);
        for (int i = 2; i < n; ++i) scanf("%d", a + i);
        for (int i = 2; i < n; ++i) scanf("%d", b + i);
        for (int i = 2; i < n; ++i) scanf("%d", c + i);
        seg.build(1, 2, n - 1);
        char op[10];
        char ch;
        int x, y;
        while (q--) {
            scanf("%s", op);
            switch (op[0]) {
                case 'q':
                    scanf("%d%d", &x, &y);
                    printf("%lld\n", (get(y) - get(x - 1) + p) % p);
                    break;
                case 's':
                    scanf(" %c[%d]=%d", &ch, &x, &y);
                    switch (ch) {
                        case 'F':
                            f[x] = y;
                            break;
                        case 'a':
                            a[x] = y;
                            break;
                        case 'b':
                            b[x] = y;
                            break;
                        case 'c':
                            c[x] = y;
                            break;
                    }
                    if (ch != 'F') {
                        seg.update(1, 2, n - 1, x);
                    }
                    break;
            }
        }
    }
    return 0;
}
