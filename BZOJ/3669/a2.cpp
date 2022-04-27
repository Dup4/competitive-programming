#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
const int INF = 0x3f3f3f3f;
int n, m;
struct Edge {
    int u, v, a, b;
    void scan() {
        scanf("%d%d%d%d", &u, &v, &a, &b);
    }
    bool operator<(const Edge &other) const {
        return a < other.a;
    }
} e[N];

struct LCT {
#define ls t[x].son[0]
#define rs t[x].son[1]
    struct node {
        int fa, son[2];
        int v, id;
        //翻转标记
        bool r;
        node() {
            fa = son[0] = son[1] = 0;
            r = 0;
            v = id = 0;
        }
    } t[N];
    int sta[N], top;
    void init(int n) {
        for (int i = 0; i <= n + m; ++i) t[i] = node();
    }
    //如果x是所在链的根返回1
    inline bool isroot(int x) {
        return t[t[x].fa].son[0] != x && t[t[x].fa].son[1] != x;
    }
    //上传信息
    inline void pushup(int x) {
        t[x].id = x;
        if (ls && t[t[ls].id].v > t[t[x].id].v)
            t[x].id = t[ls].id;
        if (rs && t[t[rs].id].v > t[t[x].id].v)
            t[x].id = t[rs].id;
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
    int query(int u, int v) {
        split(u, v);
        return t[v].id;
    }
} lct;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) e[i].scan();
    sort(e + 1, e + 1 + m);
    lct.init(n + m);
    for (int i = 1; i <= n; ++i) lct.t[i].id = i;
    for (int i = 1; i <= m; ++i) lct.t[n + i].id = n + i, lct.t[n + i].v = e[i].b;
    int ans = INF;
    for (int i = 1; i <= m; ++i) {
        int u = e[i].u, v = e[i].v, a = e[i].a, b = e[i].b;
        if (u == v)
            continue;
        if (lct.findroot(u) == lct.findroot(v)) {
            int id = lct.query(u, v);
            if (e[id - n].b <= b)
                continue;
            lct.cut(id, e[id - n].u);
            lct.cut(id, e[id - n].v);
        }
        lct.link(i + n, u);
        lct.link(i + n, v);
        if (lct.findroot(1) == lct.findroot(n)) {
            int id = lct.query(1, n);
            ans = min(ans, a + lct.t[id].v);
        }
    }
    printf("%d\n", ans == INF ? -1 : ans);
    return 0;
}
