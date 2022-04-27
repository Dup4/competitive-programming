#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
int n, rt, vis[N];
ll a[N], k, res;
vector<vector<int>> G;
struct Treap {
    struct node {
        //父亲的pri大于儿子的pri
        int key, sze, pri, son[2];
    } t[N];
    //节点编号从１开始
    int tot, rt;
    inline void init() {
        tot = rt = 0;
    }
    //手写随机数
    inline int random() {
        static int seed = 703;
        return seed = int(seed * 48217ll % 2147483647);
    }
    //新建节点
    inline int newnode(int key) {
        ++tot;
        t[tot].key = key;
        t[tot].pri = random();
        t[tot].sze = 1;
        t[tot].son[0] = t[tot].son[1] = 0;
        return tot;
    }
    // 0 左旋　1 右旋
    inline void rotate(int &x, int p) {
        int y = t[x].son[!p];
        t[x].sze = t[x].sze - t[y].sze + t[t[y].son[p]].sze;
        t[x].son[!p] = t[y].son[p];
        t[y].sze = t[y].sze - t[t[y].son[p]].sze + t[x].sze;
        t[y].son[p] = x;
        x = y;
    }
    //插入节点
    void insert(int &x, int key) {
        if (!x)
            x = newnode(key);
        else {
            ++t[x].sze;
            int p = key < t[x].key;
            insert(t[x].son[!p], key);
            if (t[x].pri < t[t[x].son[!p]].pri)
                rotate(x, p);
        }
    }
    //删除值为key的节点
    void remove(int &x, int key) {
        if (t[x].key == key) {
            if (t[x].son[0] && t[x].son[1]) {
                int p = t[t[x].son[0]].pri > t[t[x].son[1]].pri;
                rotate(x, p);
                remove(t[x].son[p], key);
            } else {
                if (!t[x].son[0])
                    x = t[x].son[1];
                else
                    x = t[x].son[0];
            }
        } else {
            --t[x].sze;
            int p = t[x].key > key;
            remove(t[x].son[!p], key);
        }
    }
    //找出第p小的节点的编号
    int getKth(int &x, int p) {
        if (p == t[t[x].son[0]].sze + 1)
            return x;
        if (p > t[t[x].son[0]].sze + 1)
            return getKth(t[x].son[1], p - t[t[x].son[0]].sze - 1);
        else
            return getKth(t[x].son[0], p);
    }
    //找出值小于等于key的节点个数
    int getRank(int &x, int key) {
        if (!x)
            return 0;
        if (t[x].key <= key)
            return t[t[x].son[0]].sze + 1 + getRank(t[x].son[1], key);
        else
            return getRank(t[x].son[0], key);
    }
    //得到最大值
    int getMax(int r) {
        while (t[r].son[1]) r = t[r].son[1];
        return t[r].key;
    }
    //得到最小值
    int getMin(int r) {
        while (t[r].son[0]) r = t[r].son[0];
        return t[r].key;
    }
    //得到根节点的前驱
    int getPre() {
        int x = t[rt].son[0];
        if (!x)
            return 0;
        while (t[x].son[1]) x = t[x].son[1];
        return x;
    }
    //得到根节点的后继
    int getNx() {
        int x = t[rt].son[1];
        if (!x)
            return 0;
        while (t[x].son[0]) x = t[x].son[0];
        return x;
    }
} treap;
void DFS(int u) {
    treap.insert(treap.rt, a[u]);
    ll t;
    if (a[u] == 0)
        t = 1e9;
    else
        t = k / a[u];
    t = min(t, 1000000000ll);
    res -= treap.getRank(treap.rt, t);
    for (auto &v : G[u]) DFS(v);
    res += treap.getRank(treap.rt, t);
}

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d%lld", &n, &k);
        G.clear();
        G.resize(n + 1);
        memset(vis, 0, sizeof vis);
        res = 0;
        treap.init();
        for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            vis[v] = 1;
        }
        for (int i = 1; i <= n; ++i)
            if (!vis[i])
                rt = i;
        DFS(rt);
        printf("%lld\n", res);
    }
    return 0;
}
