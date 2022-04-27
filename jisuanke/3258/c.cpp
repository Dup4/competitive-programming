#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
int n;
struct Hash {
    int a[N], cnt;
    void init() {
        cnt = 0;
    }
    void add(int x) {
        a[++cnt] = x;
    }
    void gao() {
        sort(a + 1, a + 1 + cnt);
        cnt = unique(a + 1, a + 1 + cnt) - a - 1;
    }
    int get(int x) {
        return lower_bound(a + 1, a + 1 + cnt, x) - a;
    }
} hs;
struct node {
    int a, b, c;
    void scan() {
        scanf("%d%d%d", &a, &b, &c);
        hs.add(a);
        hs.add(b);
        hs.add(c);
    }
} a[N];
int res[N];

struct qnode {
    // 0插入　1询问
    int a, b, id, op;
    qnode() {}
    qnode(int a, int b, int id, int op) : a(a), b(b), id(id), op(op) {}
};

struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) {
            a[x] += v;
        }
    }
    int query(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) {
            res += a[x];
        }
        return res;
    }
    int query(int l, int r) {
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
} bit[3];

int main() {
    while (scanf("%d", &n) != EOF) {
        hs.init();
        for (int i = 1; i <= n; ++i) a[i].scan();
        hs.gao();
        for (int i = 1; i <= n; ++i) {
            a[i].a = hs.get(a[i].a);
            a[i].b = hs.get(a[i].b);
            a[i].c = hs.get(a[i].c);
            //	printf("%d %d %d %d\n", i, a[i].a, a[i].b, a[i].c);
        }
        for (int i = 0; i < 3; ++i) bit[i].init();
        for (int i = 1; i <= n; ++i) {
            bit[0].update(a[i].a, 1);
            bit[1].update(a[i].b, 1);
            bit[2].update(a[i].c, 1);
        }
        int m = hs.cnt;
        for (int i = 1; i <= n; ++i) res[i] = n - 1;
        for (int i = 1; i <= n; ++i) {
            bit[0].update(a[i].a, -1);
            bit[1].update(a[i].b, -1);
            bit[2].update(a[i].c, -1);
            res[i] -= bit[1].query(1, a[i].a - 1);
            res[i] -= bit[2].query(1, a[i].b - 1);
            res[i] -= bit[0].query(a[i].b + 1, m);
            res[i] -= bit[1].query(a[i].c + 1, m);
            bit[0].update(a[i].a, 1);
            bit[1].update(a[i].b, 1);
            bit[2].update(a[i].c, 1);
        }
        //必胜容斥
        vector<qnode> vec;
        bit[0].init();
        for (int i = 1; i <= n; ++i) {
            vec.push_back(qnode(a[i].b, a[i].c, i, 0));
            vec.push_back(qnode(a[i].a, a[i].b, i, 1));
        }
        sort(vec.begin(), vec.end(), [](qnode x, qnode y) {
            if (x.a != y.a)
                return x.a < y.a;
            if (x.b != y.b)
                return x.b > y.b;
            return x.op > y.op;
        });
        for (auto it : vec) {
            if (it.op == 0) {
                bit[0].update(it.b, 1);
            } else {
                res[it.id] += bit[0].query(1, it.b - 1);
            }
        }

        //必败容斥
        vec.clear();
        bit[0].init();
        for (int i = 1; i <= n; ++i) {
            vec.push_back(qnode(a[i].a, a[i].b, i, 0));
            vec.push_back(qnode(a[i].b, a[i].c, i, 1));
        }
        sort(vec.begin(), vec.end(), [](qnode x, qnode y) {
            if (x.a != y.a)
                return x.a > y.a;
            if (x.b != y.b)
                return x.b < y.b;
            return x.op > y.op;
        });
        for (auto it : vec) {
            if (it.op == 0) {
                bit[0].update(it.b, 1);
            } else {
                res[it.id] += bit[0].query(it.b + 1, m);
            }
        }

        for (int i = 1; i <= n; ++i) printf("%d\n", res[i]);
    }
    return 0;
}
