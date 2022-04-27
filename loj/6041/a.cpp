#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
const int ALP = 22;
int n, q, ans[N];
char s[N];
struct qnode {
    int l, id;
};
struct pnode {
    int u, len;
};
vector<vector<pnode>> add;
vector<vector<qnode>> qvec;
struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x > 0; x -= x & -x) a[x] = max(a[x], v);
    }
    int query(int x) {
        int res = 0;
        for (; x < N; x += x & -x) res = max(res, a[x]);
        return res;
    }
} bit;
struct SAM {
    //空间开两倍，节点个数是两倍字符串长度
    // maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
    // minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1
    // fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小
    // c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
    // pos表示那个结点在字符串的endpos的最小值，即firstpos
    struct node {
        int maxlen, fa, nx[ALP];
        set<int> se;
        node() {
            maxlen = fa = 0;
            memset(nx, 0, sizeof nx);
            se.clear();
        }
    } t[N << 1];
    int tot, lst;
    struct Edge {
        int v, nx;
    } e[N << 1];
    int h[N << 1];
    inline void addedge(int u, int v) {
        e[++*h] = {v, h[u]};
        h[u] = *h;
    }
    inline int newnode() {
        ++tot;
        t[tot] = node();
        return tot;
    }
    inline void init() {
        tot = 0;
        lst = newnode();
    }
    inline void extend(int id, int pos) {
        int cur = newnode(), p;
        t[cur].se.insert(pos);
        t[cur].maxlen = t[lst].maxlen + 1;
        for (p = lst; p && !t[p].nx[id]; p = t[p].fa) t[p].nx[id] = cur;
        if (!p) {
            t[cur].fa = 1;
        } else {
            int q = t[p].nx[id];
            if (t[q].maxlen == t[p].maxlen + 1) {
                t[cur].fa = q;
            } else {
                int clone = newnode();
                t[clone] = t[q];
                t[clone].se.clear();
                t[clone].maxlen = t[p].maxlen + 1;
                for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
                t[cur].fa = t[q].fa = clone;
            }
        }
        lst = cur;
    }
    void DFS(int u) {
        for (int i = h[u]; i; i = e[i].nx) {
            int v = e[i].v;
            DFS(v);
            set<int> &Su = t[u].se, &Sv = t[v].se;
            if (Sv.size() > Su.size())
                swap(Su, Sv);
            for (auto &it : Sv) {
                auto nx = Su.lower_bound(it);
                if (nx != Su.begin()) {
                    --nx;
                    add[it].push_back({*nx, t[u].maxlen});
                    ++nx;
                }
                if (nx != Su.end()) {
                    add[*nx].push_back({it, t[u].maxlen});
                }
            }
            for (auto &it : Sv) Su.insert(it);
        }
    }
    //字符串从0开始
    void build(char *s) {
        init();
        for (int i = 0; s[i]; ++i) {
            extend(s[i] - '0', i + 1);
        }
        memset(h, 0, sizeof h);
        for (int i = 2; i <= tot; ++i)
            if (t[i].fa)
                addedge(t[i].fa, i);
        DFS(1);
    }
} sam;

int main() {
    scanf("%d%d%s", &n, &q, s);
    add.clear();
    add.resize(n + 1);
    qvec.clear();
    qvec.resize(n + 1);
    bit.init();
    sam.build(s);
    for (int i = 1, l, r; i <= q; ++i) {
        scanf("%d%d", &l, &r);
        qvec[r].push_back({l, i});
    }
    for (int i = 1; i <= n; ++i) {
        for (auto &it : add[i]) bit.update(it.u, it.len);
        for (auto &it : qvec[i]) ans[it.id] = bit.query(it.l);
    }
    for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
    return 0;
}
