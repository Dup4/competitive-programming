#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, k;
int res[N];
struct node {
    int a, b, c;
    void scan() {
        scanf("%d%d%d", &a, &b, &c);
    }
    bool operator<(const node &other) const {
        if (a != other.a) {
            return a < other.a;
        } else if (b != other.b) {
            return b < other.b;
        } else {
            return c < other.c;
        }
    }
    bool operator==(const node &other) const {
        return a == other.a && b == other.b && c == other.c;
    }
} qrr[N];

struct SPLAY {
    struct node {
        int son[2];
        int val, cnt, sze, fa;
    } t[N * 10];
    int root[N], tot;
    void init() {
        memset(root, 0, sizeof root);
        tot = 0;
    }
    void pushup(int x) {
        t[x].sze = t[t[x].son[0]].sze + t[t[x].son[1]].sze + t[x].cnt;
    }
    void rotate(int x) {
        int y = t[x].fa;
        int z = t[y].fa;
        int k = t[y].son[1] == x;
        t[x].fa = z;
        t[z].son[t[z].son[1] == y] = x;
        t[y].son[k] = t[x].son[k ^ 1];
        t[t[x].son[k ^ 1]].fa = y;
        t[y].fa = x;
        t[x].son[k ^ 1] = y;
        pushup(y);
        pushup(x);
    }
    void splay(int &rt, int x, int tar) {
        while (t[x].fa != tar) {
            int y = t[x].fa;
            int z = t[y].fa;
            if (z != tar) {
                (t[z].son[1] == y) ^ (t[y].son[1] == x) ? rotate(x) : rotate(y);
            }
            rotate(x);
        }
        if (tar == 0) {
            rt = x;
        }
    }
    void insert(int &rt, int x, int cnt) {
        int u = rt, fa = 0;
        while (u && t[u].val != x) {
            fa = u;
            u = t[u].son[x > t[u].val];
        }
        if (u) {
            t[u].cnt += cnt;
            t[u].sze += cnt;
        } else {
            u = ++tot;
            if (fa) {
                t[fa].son[x > t[fa].val] = u;
            }
            t[u].val = x;
            t[u].son[0] = t[u].son[1] = 0;
            t[u].cnt = t[u].sze = cnt;
            t[u].fa = fa;
        }
        pushup(u);
        splay(rt, u, 0);
    }
    int get(int &rt, int x) {
        int u = rt;
        int res = 0;
        while (u) {
            int ls = t[u].son[0];
            int rs = t[u].son[1];
            if (x < t[u].val) {
                u = ls;
            } else {
                res += t[u].cnt + t[ls].sze;
                if (x == t[u].val) {
                    break;
                }
                u = rs;
            }
        }
        return res;
    }
} sp;

struct BIT {
    void update(int x, int c, int v) {
        for (; x < N; x += x & -x) {
            sp.insert(sp.root[x], c, v);
        }
    }
    int query(int x, int c) {
        int res = 0;
        for (; x > 0; x -= x & -x) {
            res += sp.get(sp.root[x], c);
        }
        return res;
    }
} bit;

void init() {
    sp.init();
}
int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        init();
        for (int i = 1; i <= n; ++i) {
            qrr[i].scan();
        }
        sort(qrr + 1, qrr + 1 + n);
        for (int i = 1, c = 0; i <= n; ++i) {
            ++c;
            if (i != n && qrr[i] == qrr[i + 1])
                continue;
            res[bit.query(qrr[i].b, qrr[i].c) + c - 1] += c;
            bit.update(qrr[i].b, qrr[i].c, c);
            c = 0;
        }
        for (int i = 0; i < n; ++i) {
            printf("%d\n", res[i]);
        }
    }
    return 0;
}
