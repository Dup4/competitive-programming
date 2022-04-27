#include <bits/stdc++.h>
using namespace std;
const int N = 6e5 + 10;
const int ALP = 26;
int n, q, mask;
char s[N * 5];
void get(int mask) {
    scanf("%s", s);
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        mask = (mask * 131 + i) % len;
        swap(s[i], s[mask]);
    }
}

struct LCT {
#define ls t[x].son[0]
#define rs t[x].son[1]
    struct node {
        int fa, son[2];
        int v, add;
        node() {
            fa = son[0] = son[1] = 0;
            v = add = 0;
        }
        void up(int x) {
            v += x;
            add += x;
        }
    } t[N << 1];
    int sta[N << 1], top;
    //如果x是所在链的根返回1
    bool isroot(int x) {
        return t[t[x].fa].son[0] != x && t[t[x].fa].son[1] != x;
    }
    //判断并且释放lazy
    void pushdown(int x) {
        int &add = t[x].add;
        if (add) {
            if (ls)
                t[ls].up(add);
            if (rs)
                t[rs].up(add);
            add = 0;
        }
    }
    void rotate(int x) {
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
    }
    //把x弄到根
    void splay(int x) {
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
    }
    //把x到原图的同一个联通块的root弄成一条链，放在同一个splay中
    void access(int x) {
        for (int y = 0; x; y = x, x = t[x].fa) {
            splay(x);
            rs = y;
        }
    }
    void link(int x, int y) {
        t[x].fa = y;
        access(y);
        splay(y);
        t[y].up(t[x].v);
    }
    void cut(int x) {
        access(x);
        splay(x);
        if (ls) {
            t[ls].up(-t[x].v);
            t[ls].fa = 0;
            ls = 0;
        }
    }
} lct;

struct SAM {
    //空间开两倍，节点个数是两倍字符串长度
    // maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
    // minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1
    // fa 表示节点i的后缀链接
    // lct.t[i].v 表示节点i的endpos集合大小
    struct node {
        int maxlen, fa, nx[ALP];
        void init() {
            maxlen = fa = 0;
            memset(nx, 0, sizeof nx);
        }
    } t[N << 1];
    int tot, lst;
    inline int newnode() {
        ++tot;
        t[tot].init();
        lct.t[tot] = LCT::node();
        return tot;
    }
    inline void init() {
        tot = 0;
        lst = newnode();
    }
    inline void extend(int id) {
        int cur = newnode(), p;
        // t[cur].cnt = 1;
        lct.t[cur].v = 1;
        t[cur].maxlen = t[lst].maxlen + 1;
        for (p = lst; p && !t[p].nx[id]; p = t[p].fa) t[p].nx[id] = cur;
        if (!p) {
            t[cur].fa = 1;
            lct.link(cur, 1);
        } else {
            int q = t[p].nx[id];
            if (t[q].maxlen == t[p].maxlen + 1) {
                t[cur].fa = q;
                lct.link(cur, q);
            } else {
                int clone = newnode();
                t[clone] = t[q];
                lct.link(clone, t[q].fa);
                t[clone].maxlen = t[p].maxlen + 1;
                for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
                t[cur].fa = t[q].fa = clone;
                lct.cut(q);
                lct.link(q, clone);
                lct.link(cur, clone);
            }
        }
        lst = cur;
    }
    //字符串从0开始
    void build(char *s) {
        init();
        for (int i = 0; s[i]; ++i) {
            extend(s[i] - 'A');
        }
    }
    void add() {
        get(mask);
        for (int i = 0; s[i]; ++i) extend(s[i] - 'A');
    }
    int query() {
        get(mask);
        int p = 1;
        for (int i = 0; s[i]; ++i) {
            int ch = s[i] - 'A';
            if (!t[p].nx[ch])
                return 0;
            p = t[p].nx[ch];
        }
        lct.splay(p);
        return lct.t[p].v;
    }
} sam;

int main() {
    while (scanf("%d", &q) != EOF) {
        mask = 0;
        scanf("%s", s);
        sam.build(s);
        char op[10];
        while (q--) {
            scanf("%s", op);
            if (*op == 'A')
                sam.add();
            else {
                int ans = sam.query();
                printf("%d\n", ans);
                mask ^= ans;
            }
        }
    }
    return 0;
}
