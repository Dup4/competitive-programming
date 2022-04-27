#include <bits/stdc++.h>
using namespace std;

/*
        BZOJ 1552
    有n个数，通过区间翻转来进行排序
    先找到编号最小的物品的位置p1, 将区间[1, p1]翻转
    再找到编号第二小的物品的位置p2，将区间[2, p2]翻转
    如果存在多个相同的编号，则按输入顺序操作
        要求输出n个数，表示第i小的编号的物品当前所处的位置

        每次翻转哪个物品可以预处理
        这样就可以对应到下标，再将下标存到Splay中，维护区间翻转即可
*/

#define INF 0x3f3f3f3f
#define N 100010
#define pii pair<int, int>
#define fi first
#define se second
int n, a[N];
pii b[N];

struct SPLAY {
    struct node {
        int son[2];
        int val, fa, sze, lazy;
        node() {}
        node(int fa, int val) {
            this->fa = fa;
            this->val = val;
            son[0] = son[1] = 0;
            lazy = 0;
            sze = 1;
        }
        void rev() {
            swap(son[0], son[1]);
            lazy ^= 1;
        }
    } t[N];
    int rt, tot;
    int Sta[N], Top;
    void init() {
        rt = tot = 0;
    }
    void pushup(int x) {
        t[x].sze = 1 + t[t[x].son[0]].sze + t[t[x].son[1]].sze;
    }
    void rotate(int x) {
        int y = t[x].fa;
        int z = t[y].fa;
        int k = (t[y].son[1] == x);
        t[x].fa = z;
        t[z].son[t[z].son[1] == y] = x;
        t[y].son[k] = t[x].son[k ^ 1];
        t[t[x].son[k ^ 1]].fa = y;
        t[y].fa = x;
        t[x].son[k ^ 1] = y;
        pushup(y);
        pushup(x);
    }
    void pushdown(int x) {
        int &lazy = t[x].lazy;
        if (!lazy) {
            return;
        }
        t[t[x].son[0]].rev();
        t[t[x].son[1]].rev();
        lazy = 0;
    }
    void splay(int x, int tar) {
        Sta[Top = 1] = x;
        //要从上往下pushdown
        for (int i = x; i != rt; i = t[i].fa) {
            Sta[++Top] = t[i].fa;
        }
        while (Top) {
            pushdown(Sta[Top--]);
        }
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
    void insert(int x) {
        int u = rt, fa = 0;
        while (u && t[u].val != x) {
            fa = u;
            u = t[u].son[x > t[u].val];
        }
        u = ++tot;
        if (fa) {
            t[fa].son[x > t[fa].val] = u;
        }
        t[u] = node(fa, x);
        splay(u, 0);
    }
    //找x的排名 即翻转后的x在新序列中所处的位置
    int Rank(int x) {
        splay(x, 0);
        return t[t[x].son[0]].sze + 1;
    }
    //根据排名找Splay中的下标
    int kth(int k) {
        int u = rt;
        while (1) {
            if (t[u].lazy) {
                pushdown(u);
            }
            int ls = t[u].son[0];
            int rs = t[u].son[1];
            int tot = t[ls].sze + 1;
            if (tot == k) {
                return u;
            } else if (tot > k) {
                u = ls;
            } else {
                k -= tot;
                u = rs;
            }
        }
        return 0;
    }
    void Del(int x) {
        int R = Rank(x);
        int l = kth(R - 1);
        int r = kth(R + 1);
        splay(l, 0);
        splay(r, l);
        t[r].son[0] = 0;
        pushup(r);
        pushup(l);
    }
    void Reverse(int l, int r) {
        int pre = kth(l - 1);
        int nx = kth(r + 1);
        splay(pre, 0);
        splay(nx, pre);
        if (t[nx].son[0] != 0) {
            t[t[nx].son[0]].rev();
        }
    }
    void output(int x) {
        if (!x) {
            return;
        }
        output(t[x].son[0]);
        printf("%d %d\n", x, t[x].val);
        output(t[x].son[1]);
    }
} sp;

int main() {
    while (scanf("%d", &n) != EOF) {
        sp.init();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            b[i] = pii(a[i], i);
        }
        for (int i = 1; i <= n; ++i) {
            sp.insert(i);
        }
        sort(b + 1, b + 1 + n);
        //插入两个哨兵 防止找不到前驱和后继
        sp.insert(-INF);
        sp.insert(INF);
        for (int i = 1; i <= n; ++i) {
            int x = b[i].se;
            int y = sp.Rank(b[i].se);
            printf("%d%c", y + i - 2, " \n"[i == n]);
            //因为存在一个哨兵，所以从2开始
            sp.Reverse(2, y);
            //每次取出后删掉该元素
            sp.Del(x);
        }
    }
    return 0;
}
