#include <bits/stdc++.h>
using namespace std;

#define N 1000010
#define M 1000000
int n, m, q, a[N], b[N];

struct SEG {
    struct node {
        int sum, Max;
        node() {
            sum = Max = 0;
        }
        node(int sum, int Max) : sum(sum), Max(Max) {}
        node operator+(const node &other) const {
            node res = node();
            res.sum = sum + other.sum;
            res.Max = max(other.Max, Max + other.sum);
            return res;
        }
    } t[N << 2];
    void init() {
        memset(t, 0, sizeof t);
    }
    void update(int id, int l, int r, int x, int v) {
        if (l == r) {
            t[id].sum += v;
            t[id].Max += v;
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(id << 1, l, mid, x, v);
        else
            update(id << 1 | 1, mid + 1, r, x, v);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    int query(int id, int l, int r, node tmp) {
        if (l == r) {
            return l;
        }
        int mid = (l + r) >> 1;
        node tmp2 = t[id << 1 | 1] + tmp;
        if (tmp2.Max > 0) {
            return query(id << 1 | 1, mid + 1, r, tmp);
        } else {
            return query(id << 1, l, mid, tmp2);
        }
    }
} seg;

template <class T>
void read(T &x) {
    x = 0;
    char ch;
    while (!isdigit(ch = getchar()))
        ;
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
}
template <class T>
void out(T x) {
    if (x / 10)
        out(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        seg.init();
        for (int i = 1; i <= n; ++i) {
            read(a[i]);
            seg.update(1, 1, M, a[i], 1);
        }
        for (int i = 1; i <= m; ++i) {
            read(b[i]);
            seg.update(1, 1, M, b[i], -1);
        }
        read(q);
        int op, x, v;
        while (q--) {
            read(op);
            read(x);
            read(v);
            switch (op) {
                case 1:
                    seg.update(1, 1, M, a[x], -1);
                    seg.update(1, 1, M, a[x] = v, 1);
                    break;
                case 2:
                    seg.update(1, 1, M, b[x], 1);
                    seg.update(1, 1, M, b[x] = v, -1);
                    break;
                default:
                    assert(0);
            }
            if (seg.t[1].Max <= 0) {
                puts("-1");
            } else {
                out(seg.query(1, 1, M, SEG::node(0, 0)));
                puts("");
            }
        }
    }
    return 0;
}
