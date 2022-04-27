#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int(x.size()))
const int N = 2e4 + 10;
int n, m, q, a[N];

struct Hash {
    vector<int> a;
    int &operator[](int x) {
        return a[x - 1];
    }
    int size() {
        return a.size();
    }
    void init() {
        a.clear();
    }
    void add(int x) {
        a.push_back(x);
    }
    void gao() {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }
    int get(int x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
} hs;

struct SEG {
    struct node {
        int ls, rs, sum;
        void init() {
            ls = rs = sum = 0;
        }
    } t[N * 50];
    int tot;
    int newnode() {
        ++tot;
        t[tot].init();
        return tot;
    }
    void init() {
        tot = 0;
    }
    void update(int &rt, int l, int r, int pos, int v) {
        if (!rt)
            rt = newnode();
        t[rt].sum += v;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[rt].ls, l, mid, pos, v);
        else
            update(t[rt].rs, mid + 1, r, pos, v);
    }
    int query(int l, int r, int k, vector<int> &L, vector<int> &R) {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        int lsum = 0, rsum = 0;
        for (int i = 0; i < SZ(L); ++i) lsum += t[t[L[i]].ls].sum;
        for (int i = 0; i < SZ(R); ++i) rsum += t[t[R[i]].ls].sum;
        if (rsum - lsum >= k) {
            for (int i = 0; i < SZ(L); ++i) L[i] = t[L[i]].ls;
            for (int i = 0; i < SZ(R); ++i) R[i] = t[R[i]].ls;
            return query(l, mid, k, L, R);
        } else {
            for (int i = 0; i < SZ(L); ++i) L[i] = t[L[i]].rs;
            for (int i = 0; i < SZ(R); ++i) R[i] = t[R[i]].rs;
            return query(mid + 1, r, k - (rsum - lsum), L, R);
        }
    }
} seg;

struct BIT {
    int rt[N], n;
    void init(int _n) {
        n = _n;
        memset(rt, 0, sizeof(rt[0]) * (n + 5));
        seg.init();
    }
    int lowbit(int x) {
        return x & -x;
    }
    void update(int x, int pos, int v) {
        for (int i = x; i <= n; i += lowbit(i)) seg.update(rt[i], 1, m, pos, v);
    }
    vector<int> get(int x) {
        vector<int> vec;
        for (int i = x; i; i -= lowbit(i)) vec.push_back(rt[i]);
        return vec;
    }
    int query(int l, int r, int k) {
        vector<int> L(get(l - 1)), R(get(r));
        return seg.query(1, m, k, L, R);
    }
} bit;

struct E {
    int op, x, y, z;
    E() {}
    E(int op, int x, int y, int z) : op(op), x(x), y(y), z(z) {}
} e[N];

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        hs.init();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            hs.add(a[i]);
        }
        scanf("%d", &q);
        for (int i = 1, x, y, z; i <= q; ++i) {
            static char op[10];
            scanf("%s", op);
            scanf("%d%d", &x, &y);
            if (op[0] == 'C') {
                e[i] = E(1, x, y, 0);
                hs.add(y);
            } else if (op[0] == 'Q') {
                scanf("%d", &z);
                e[i] = E(2, x, y, z);
            }
        }
        hs.gao();
        m = hs.size();
        for (int i = 1; i <= n; ++i) a[i] = hs.get(a[i]);
        for (int i = 1; i <= q; ++i)
            if (e[i].op == 1)
                e[i].y = hs.get(e[i].y);
        bit.init(n);
        for (int i = 1; i <= n; ++i) {
            bit.update(i, a[i], 1);
        }
        for (int i = 1; i <= q; ++i) {
            if (e[i].op == 2) {
                printf("%d\n", hs[bit.query(e[i].x, e[i].y, e[i].z)]);
            } else {
                bit.update(e[i].x, a[e[i].x], -1);
                a[e[i].x] = e[i].y;
                bit.update(e[i].x, a[e[i].x], 1);
            }
        }
    }
    return 0;
}
