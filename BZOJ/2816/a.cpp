#include <bits/stdc++.h>
using namespace std;
#define pII pair<int, int>
#define fi first
#define se second
const int N = 1e5 + 10;
int n, m, q, C, v[N], d[N][10];
map<pII, int> mp;
struct LCT {
#define ls t[x].son[0]
#define rs t[x].son[1]
    struct node {
        int fa, son[2];
        int v, Max;
        //翻转标记
        bool r;
        node() {
            fa = son[0] = son[1] = 0;
            v = Max = 0;
            r = 0;
        }
    } t[N];
    int sta[N], top;
    //如果x是所在链的根返回1
    inline bool isroot(int x) {
        return t[t[x].fa].son[0] != x && t[t[x].fa].son[1] != x;
    }
    //上传信息
    inline void pushup(int x) {
        t[x].Max = t[x].v;
        if (ls)
            t[x].Max = max(t[x].Max, t[ls].Max);
        if (rs)
            t[x].Max = max(t[x].Max, t[rs].Max);
    }
    //翻转操作
    inline void pushr(int x) {
        swap(ls, rs);
        t[x].r ^= 1;
    }
    //判断并且释放lazy
    inline void pushdown(int x) {
        if (t[x].r) {
            if (ls)
                pushr(ls);
            if (rs)
                pushr(rs);
            t[x].r = 0;
        }
    }
    inline void rotate(int x) {
        int y = t[x].fa, z = t[y].fa;
        int k = t[y].son[1] == x, w = t[x].son[!k];
        if (!isroot(y)) {
            t[z].son[t[z].son[1] == y] = x;
        }
        t[x].son[!k] = y;
        t[y].son[k] = w;
        if (w) {
            t[w].fa = y;
        }
        t[y].fa = x;
        t[x].fa = z;
        pushup(y);
    }
    //把x弄到根
    inline void splay(int x) {
        sta[++top] = x;
        for (int it = x; !isroot(it); it = t[it].fa) sta[++top] = t[it].fa;
        while (top) pushdown(sta[top--]);
        while (!isroot(x)) {
            int y = t[x].fa, z = t[y].fa;
            //此处和普通的splay不同
            if (!isroot(y)) {
                ((t[y].son[0] == x) ^ (t[z].son[0] == y)) ? rotate(x) : rotate(y);
            }
            rotate(x);
        }
        pushup(x);
    }
    //把x到原图的同一个联通块的root弄成一条链，放在同一个splay中
    inline void access(int x) {
        for (int y = 0; x; y = x, x = t[x].fa) {
            splay(x);
            rs = y;
            pushup(x);
        }
    }
    //把x拎作原图的根
    inline void makeroot(int x) {
        access(x);
        splay(x);
        pushr(x);
    }
    //找到x所在联通块的splay的根
    inline int findroot(int x) {
        access(x);
        splay(x);
        //更稳妥的写法
        while (ls) pushdown(x), x = ls;
        splay(x);
        return x;
    }
    //把x到y的路径抠出来
    inline void split(int x, int y) {
        //先把x弄成原图的根
        makeroot(x);
        //再把y到根(x)的路径弄成重链
        access(y);
        //然后再让y成为splay的根，那么y的左子树中就是这条链的点
        splay(y);
    }
    //连接x, y所在的两个联通块
    inline void link(int x, int y) {
        makeroot(x);
        if (findroot(y) != x)
            t[x].fa = y;
    }
    //隔断x, y所在的两个联通块
    inline void cut(int x, int y) {
        makeroot(x);
        if (findroot(y) == x && t[y].fa == x && !t[y].son[0]) {
            t[y].fa = t[x].son[1] = 0;
            pushup(x);
        }
    }
} lct[10];

void init() {
    mp.clear();
    memset(d, 0, sizeof d);
    for (int i = 0; i < C; ++i)
        for (int j = 0; j <= n; ++j) {
            lct[i].t[j] = LCT::node();
            lct[i].t[j].v = lct[i].t[j].Max = v[j];
        }
}
int main() {
    while (scanf("%d%d%d%d", &n, &m, &C, &q) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", v + i);
        init();
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            if (u > v)
                swap(u, v);
            ++d[u][w];
            ++d[v][w];
            lct[w].link(u, v);
            mp[pII(u, v)] = w;
        }
        int op, u, v, w, x, y, c;
        while (q--) {
            scanf("%d", &op);
            if (op == 0) {
                scanf("%d%d", &x, &y);
                for (int i = 0; i < C; ++i) {
                    lct[i].access(x);
                    lct[i].splay(x);
                    lct[i].t[x].v = y;
                }
            } else if (op == 1) {
                scanf("%d%d%d", &u, &v, &w);
                if (u > v)
                    swap(u, v);
                if (mp.count(pII(u, v)) && mp[pII(u, v)] == w) {
                    puts("Success.");
                    continue;
                }
                if (!mp.count(pII(u, v)))
                    puts("No such edge.");
                else if (d[u][w] == 2 || d[v][w] == 2)
                    puts("Error 1.");
                else if (lct[w].findroot(u) == lct[w].findroot(v))
                    puts("Error 2.");
                else {
                    int pw = mp[pII(u, v)];
                    --d[u][pw];
                    --d[v][pw];
                    lct[pw].cut(u, v);
                    mp[pII(u, v)] = w;
                    ++d[u][w];
                    ++d[v][w];
                    lct[w].link(u, v);
                    puts("Success.");
                }
            } else {
                scanf("%d%d%d", &c, &u, &v);
                if (lct[c].findroot(u) != lct[c].findroot(v))
                    puts("-1");
                else {
                    lct[c].split(u, v);
                    printf("%d\n", lct[c].t[v].Max);
                }
            }
        }
    }
    return 0;
}
