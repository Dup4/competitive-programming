#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
const int p = 1e9 + 7;
int n;
int A[N << 1], B[N << 1];
struct node {
    int a, b, c;
    node() {}
    void scan() {
        scanf("%d%d%d", &a, &b, &c);
        A[++A[0]] = a - 2 * b;
        A[++A[0]] = 2 * b - a;
        B[++B[0]] = b - 2 * a;
        B[++B[0]] = 2 * a - b;
    }
} a[N];

void Hash(int *a) {
    sort(a + 1, a + 1 + a[0]);
    a[0] = unique(a + 1, a + 1 + a[0]) - a - 1;
}

int get(int *a, int x) {
    return lower_bound(a + 1, a + 1 + a[0], x) - a;
}

struct SEG {
    struct node {
        ll sum;
        node() {
            sum = 0;
        }
        node operator+(const node &other) const {
            node res = node();
            res.sum = (sum + other.sum) % p;
            return res;
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int pos, int x) {
        if (l == r) {
            (t[id].sum += x) %= p;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, x);
        else
            update(id << 1 | 1, mid + 1, r, pos, x);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    ll query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            return t[id].sum;
        }
        int mid = (l + r) >> 1;
        ll res = 0;
        if (ql <= mid)
            res = (res + query(id << 1, l, mid, ql, qr)) % p;
        if (qr > mid)
            res = (res + query(id << 1 | 1, mid + 1, r, ql, qr)) % p;
        return res;
    }
} segA, segB;

int main() {
    while (scanf("%d", &n) != EOF) {
        A[0] = B[0] = 0;
        for (int i = 1; i <= n; ++i) a[i].scan();
        Hash(A);
        Hash(B);
        segA.build(1, 1, A[0]);
        segB.build(1, 1, B[0]);
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            segA.update(1, 1, A[0], get(A, 2 * a[i].b - a[i].a), a[i].c);
            segB.update(1, 1, B[0], get(B, 2 * a[i].a - a[i].b), a[i].c);
            (res += 1ll * a[i].c * segA.query(1, 1, A[0], 1, get(A, a[i].a - 2 * a[i].b)) % p) %= p;
            (res += 1ll * a[i].c * segB.query(1, 1, B[0], 1, get(B, a[i].b - 2 * a[i].a)) % p) %= p;
        }
        printf("%lld\n", res);
    }
    return 0;
}
