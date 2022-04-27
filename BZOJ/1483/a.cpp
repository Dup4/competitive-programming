#include <bits/stdc++.h>
using namespace std;

#define N 1000010
#define INF 0x3f3f3f3f
int n, q, res;
struct Splay {
    int root[N], tot;
    struct node {
        int son[2];
        int val, fa, sze;
    } t[N * 2];
    void init() {
        memset(root, 0, sizeof root);
        tot = 0;
    }
    void pushup(int x) {
        t[x].sze = 1 + t[t[x].son[0]].sze + t[t[x].son[1]].sze;
    }
    void rotate(int x) {
        int y = t[x].fa;
        int z = t[y].fa;
        int k = t[y].son[1] == x;
        t[x].fa = z;
        t[z].son[t[z].son[1] == y] = x;
        t[t[x].son[k ^ 1]].fa = y;
        t[y].son[k] = t[x].son[k ^ 1];
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
    void insert(int &rt, int x) {
        int u = rt, fa = 0;
        while (u && x != t[u].val) {
            fa = u;
            u = t[u].son[x > t[u].val];
        }
        if (u) {
            assert(0);
        } else {
            u = ++tot;
            if (fa) {
                t[fa].son[x > t[fa].val] = u;
            }
            t[u].son[0] = t[u].son[1] = 0;
            t[u].sze = 1;
            t[u].val = x;
            t[u].fa = fa;
        }
        splay(rt, u, 0);
    }
    int Next(int &rt, int x, int f) {
        int u = rt;
        u = t[u].son[f];
        if (u == 0) {
            return -1;
        }
        while (t[u].son[f ^ 1]) {
            u = t[u].son[f ^ 1];
        }
        return t[u].val;
    }
    int merge(int now, int &rt, int pre) {
        if (now == 0) {
            return pre;
        }
        int ls = t[now].son[0], rs = t[now].son[1];
        pre = merge(ls, rt, pre);

        int x = t[now].val;
        t[now].son[0] = t[now].son[1] = 0;
        t[now].sze = 1;
        int u = rt, fa = 0;
        while (u && x != t[u].val) {
            fa = u;
            u = t[u].son[x > t[u].val];
        }
        if (fa) {
            t[fa].son[x > t[fa].val] = now;
        }
        t[now].fa = fa;
        splay(rt, now, 0);

        int y = Next(rt, x, 0);
        int z = Next(rt, x, 1);
        if (y != -1 && pre != y && y == x - 1) {
            --res;
        }
        if (z == x + 1) {
            --res;
        }

        return merge(rs, rt, x);
    }
} sp;
map<int, int> mp;
int id_cnt;
int id(int x) {
    if (mp.find(x) == mp.end()) {
        mp[x] = ++id_cnt;
    }
    return mp[x];
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        sp.init();
        res = n;
        id_cnt = 0;
        mp.clear();
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            x = id(x);
            sp.insert(sp.root[x], i);
            int y = sp.Next(sp.root[x], i, 0);
            if (i > 1) {
                if (y == i - 1) {
                    --res;
                }
            }
        }
        int op, x, y;
        while (q--) {
            scanf("%d", &op);
            switch (op) {
                case 1:
                    scanf("%d%d", &x, &y);
                    if (x == y)
                        break;
                    x = id(x), y = id(y);
                    if (sp.t[sp.root[x]].sze < sp.t[sp.root[y]].sze) {
                        sp.merge(sp.root[x], sp.root[y], -2);
                        sp.root[x] = 0;
                    } else {
                        sp.merge(sp.root[y], sp.root[x], -2);
                        swap(sp.root[x], sp.root[y]);
                        sp.root[x] = 0;
                    }
                    break;
                case 2:
                    printf("%d\n", res);
                    break;
                default:
                    assert(0);
            }
        }
    }
    return 0;
}
