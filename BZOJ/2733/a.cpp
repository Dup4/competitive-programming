#include <bits/stdc++.h>
using namespace std;

#define N 100010
struct Splay {
    int root[N], tot;
    struct node {
        int son[2];
        int val, cnt, fa, sze;
    } t[N * 40];
    void init() {
        tot = 0;
        memset(root, 0, sizeof root);
    }
    void pushup(int x) {
        t[x].sze = t[x].cnt + t[t[x].son[0]].sze + t[t[x].son[1]].sze;
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
            if (z != tar)
                (t[z].son[0] == y) ^ (t[y].son[0] == x) ? rotate(x) : rotate(y);
            rotate(x);
        }
        if (tar == 0)
            rt = x;
    }
    void insert(int &rt, int x, int cnt) {
        int u = rt, fa = t[u].fa;
        while (u && t[u].val != x) {
            fa = u;
            u = t[u].son[x > t[u].val];
        }
        if (u)
            t[u].cnt += cnt;
        else {
            u = ++tot;
            if (fa)
                t[fa].son[x > t[fa].val] = u;
            t[u].fa = fa;
            t[u].val = x;
            t[u].son[0] = t[u].son[1] = 0;
            t[u].cnt = t[u].sze = cnt;
        }
        pushup(u);
        splay(rt, u, 0);
    }
    int kth(int rt, int k) {
        int u = rt;
        if (t[u].sze < k)
            return 0;
        while (1) {
            int y = t[u].son[0];
            if (t[y].sze + t[u].cnt < k) {
                k -= t[y].sze + t[u].cnt;
                u = t[u].son[1];
            } else {
                if (t[y].sze >= k)
                    u = y;
                else
                    return t[u].val;
            }
        }
    }
    void merge(int now, int &rt) {
        if (now == 0)
            return;
        merge(t[now].son[0], rt);
        insert(rt, t[now].val, t[now].cnt);
        merge(t[now].son[1], rt);
    }
} sp;

int n, m, q;
int pre[N], sze[N];
int find(int x) {
    return pre[x] == 0 ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        if (sze[fx] > sze[fy])
            swap(fx, fy);
        pre[fx] = fy;
        sze[fy] += sze[fx];
        sp.merge(sp.root[fx], sp.root[fy]);
    }
}
int id[N];

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        sp.init();
        id[0] = -1;
        for (int i = 1; i <= n; ++i) pre[i] = 0, sze[i] = 1;
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            id[x] = i;
            sp.insert(sp.root[i], x, 1);
        }
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            join(u, v);
        }
        char op[10];
        int x, y;
        scanf("%d", &q);
        while (q--) {
            scanf("%s%d%d", op, &x, &y);
            switch (op[0]) {
                case 'B':
                    join(x, y);
                    break;
                case 'Q':
                    printf("%d\n", id[sp.kth(sp.root[find(x)], y)]);
                    break;
                default:
                    assert(0);
            }
        }
    }
    return 0;
}
