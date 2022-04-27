#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int n, q, lst, ce, cp, fa[N];

struct LctEdge {
#define ls t[x].son[0]
#define rs t[x].son[1]
    struct node {
        int fa, son[2];
        int v, sum, lazy;
        //翻转标记
        bool r;
        void init() {
            fa = son[0] = son[1] = 0;
            v = sum = 0;
            r = 0;
        }
        void up() {
            v = sum = 0;
            lazy = 1;
        }
    } t[N];
    int sta[N], top;
    //如果x是所在链的根返回1
    inline bool isroot(int x) {
        return t[t[x].fa].son[0] != x && t[t[x].fa].son[1] != x;
    }
    //上传信息
    inline void pushup(int x) {
        t[x].sum = t[ls].sum + t[rs].sum + t[x].v;
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
        if (t[x].lazy) {
            if (ls)
                t[ls].up();
            if (rs)
                t[rs].up();
            t[x].lazy = 0;
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
} lctEdge;

struct LctPoint {
#define ls t[x].son[0]
#define rs t[x].son[1]
    struct node {
        int fa, son[2];
        int v, sum;
        //翻转标记
        bool r;
        void init() {
            fa = son[0] = son[1] = 0;
            v = sum = 0;
            r = 0;
        }
    } t[N];
    int sta[N], top, outSta[N];
    //如果x是所在链的根返回1
    inline bool isroot(int x) {
        return t[t[x].fa].son[0] != x && t[t[x].fa].son[1] != x;
    }
    //上传信息
    inline void pushup(int x) {
        t[x].sum = t[ls].sum + t[rs].sum + t[x].v;
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
        top = 0;
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
    //先序遍历
    void out(int x) {
        if (x) {
            pushdown(x);
            out(ls);
            outSta[++*outSta] = x;
            out(rs);
        }
    }
} lctPoint;

int find(int x) {
    return fa[x] == 0 ? x : fa[x] = find(fa[x]);
}

int getEdge(int u, int v) {
    if (find(u) != find(v)) {
        return -1;
    }
    lctEdge.split(u, v);
    return lctEdge.t[v].sum;
}

int getPoint(int u, int v) {
    if (find(u) != find(v)) {
        return -1;
    }
    lctPoint.split(u, v);
    return lctPoint.t[v].sum;
}

void link(int u, int v) {
    int fu = find(u), fv = find(v);
    if (fu == fv) {
        lctEdge.split(u, v);
        lctEdge.t[v].up();

        if (getPoint(u, v) > 2) {
            ++cp;
            lctPoint.t[cp].init();
            lctPoint.split(u, v);
            *lctPoint.outSta = 0;
            lctPoint.out(v);
            //需要新开一个栈以避免出错  因为splay会用到原来的栈
            for (int i = 1; i < *lctPoint.outSta; ++i) {
                lctPoint.cut(lctPoint.outSta[i], lctPoint.outSta[i + 1]);
            }
            for (int i = 1; i <= *lctPoint.outSta; ++i) {
                lctPoint.link(lctPoint.outSta[i], cp);
            }
        }
    } else {
        fa[fv] = fu;
        ++ce;
        lctEdge.t[ce].init();
        lctEdge.t[ce].v = 1;
        lctEdge.link(u, ce);
        lctEdge.link(ce, v);
        lctPoint.link(u, v);
    }
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        lst = 0;
        ce = n;
        cp = n;
        memset(fa, 0, sizeof fa);
        for (int i = 1; i <= n; ++i) {
            lctEdge.t[i].init();
            lctPoint.t[i].init();
            lctPoint.t[i].v = 1;
        }
        int op, u, v;
        while (q--) {
            scanf("%d%d%d", &op, &u, &v);
            u ^= lst;
            v ^= lst;
            if (op == 1) {
                link(u, v);
            } else if (op == 2) {
                int res = getEdge(u, v);
                if (res != -1)
                    lst = res;
                printf("%d\n", res);
            } else {
                int res = getPoint(u, v);
                if (res != -1)
                    lst = res;
                printf("%d\n", res);
            }
        }
    }
    return 0;
}
