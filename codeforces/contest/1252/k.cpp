#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
int n, q;
char s[N];
struct Matrix {
    int a[2][2];
    void init() {
        a[0][0] = a[1][1] = 1;
        a[0][1] = a[1][0] = 0;
    }
    int* operator[](int x) {
        return a[x];
    }
    Matrix operator*(Matrix b) {
        Matrix res;
        res[0][0] = (1ll * a[0][0] * b[0][0] % mod + 1ll * a[0][1] * b[1][0] % mod) % mod;
        res[0][1] = (1ll * a[0][0] * b[0][1] % mod + 1ll * a[0][1] * b[1][1] % mod) % mod;
        res[1][0] = (1ll * a[1][0] * b[0][0] % mod + 1ll * a[1][1] * b[1][0] % mod) % mod;
        res[1][1] = (1ll * a[1][0] * b[0][1] % mod + 1ll * a[1][1] * b[1][1] % mod) % mod;
        return res;
    }
} A, B, res;

struct SEG {
    struct node {
        Matrix a[2];
        int lazy;
        void init() {
            a[0].init();
            a[1].init();
            lazy = 0;
        }
        void up() {
            swap(a[0], a[1]);
            lazy ^= 1;
        }
    } t[N << 2];
    void pushup(int id) {
        t[id].a[0] = t[id << 1 | 1].a[0] * t[id << 1].a[0];
        t[id].a[1] = t[id << 1 | 1].a[1] * t[id << 1].a[1];
    }
    void down(int id) {
        int& lazy = t[id].lazy;
        if (lazy) {
            t[id << 1].up();
            t[id << 1 | 1].up();
            lazy = 0;
        }
    }
    void build(int id, int l, int r) {
        if (l == r) {
            t[id].a[0] = A;
            t[id].a[1] = B;
            if (s[l] == 'B') {
                swap(t[id].a[0], t[id].a[1]);
            }
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        pushup(id);
    }
    void modify(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            t[id].up();
            return;
        }
        int mid = (l + r) >> 1;
        down(id);
        if (ql <= mid)
            modify(id << 1, l, mid, ql, qr);
        if (qr > mid)
            modify(id << 1 | 1, mid + 1, r, ql, qr);
        pushup(id);
    }
    Matrix query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr)
            return t[id].a[0];
        int mid = (l + r) >> 1;
        down(id);
        Matrix res;
        res.init();
        if (qr > mid)
            res = res * query(id << 1 | 1, mid + 1, r, ql, qr);
        if (ql <= mid)
            res = res * query(id << 1, l, mid, ql, qr);
        return res;
    }
} seg;

int main() {
    A = {1, 1, 0, 1};
    B = {1, 0, 1, 1};
    while (scanf("%d%d", &n, &q) != EOF) {
        scanf("%s", s + 1);
        seg.build(1, 1, n);
        int op, l, r, a, b;
        for (int i = 1; i <= q; ++i) {
            scanf("%d%d%d", &op, &l, &r);
            if (op == 1) {
                seg.modify(1, 1, n, l, r);
            } else {
                scanf("%d%d", &a, &b);
                res = {a, 0, b, 0};
                res = seg.query(1, 1, n, l, r) * res;
                printf("%d %d\n", res[0][0], res[1][0]);
            }
        }
    }
    return 0;
}
