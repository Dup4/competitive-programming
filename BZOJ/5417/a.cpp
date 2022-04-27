#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5e5 + 10;
const int ALP = 26;
int n, q, l, r;
char s[N], t[N];

struct SEG {
    struct node {
        int ls, rs;
        node() {
            ls = rs = 0;
        }
        node(int ls, int rs) : ls(ls), rs(rs) {}
    } t[N * 42];
    int tot;
    int newnode() {
        ++tot;
        t[tot] = node();
        return tot;
    }
    void Copy(int &x) {
        int tmp = newnode();
        t[tmp] = t[x];
        x = tmp;
    }
    void init() {
        tot = 0;
        newnode();
    }
    void update(int &now, int l, int r, int pos) {
        if (!now)
            now = newnode();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[now].ls, l, mid, pos);
        else
            update(t[now].rs, mid + 1, r, pos);
    }
    void merge(int &x, int y, int l, int r) {
        if (!x || !y) {
            x |= y;
            return;
        }
        Copy(x);
        int mid = (l + r) >> 1;
        merge(t[x].ls, t[y].ls, l, mid);
        merge(t[x].rs, t[y].rs, mid + 1, r);
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (!id || ql > qr)
            return 0;
        if (l >= ql && r <= qr)
            return 1;
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid)
            res += query(t[id].ls, l, mid, ql, qr);
        if (qr > mid)
            res += query(t[id].rs, mid + 1, r, ql, qr);
        return res;
    }
} seg;

struct SAM {
    //空间开两倍，节点个数是两倍字符串长度
    // maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
    // minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1
    // fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小
    // c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
    struct node {
        int maxlen, fa, rt, nx[ALP];
        node() {
            maxlen = fa = rt = 0;
            memset(nx, 0, sizeof nx);
        }
    } t[N << 1];
    int tot, lst;
    vector<vector<int> > G;
    inline int newnode() {
        ++tot;
        t[tot] = node();
        return tot;
    }
    inline void init() {
        tot = 0;
        lst = newnode();
    }
    inline void extend(int id) {
        int cur = newnode(), p;
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
                t[clone].rt = 0;
                t[clone].maxlen = t[p].maxlen + 1;
                for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
                t[cur].fa = t[q].fa = clone;
            }
        }
        lst = cur;
    }
    void DFS(int u) {
        for (int i = 0, sze = G[u].size(); i < sze; ++i) {
            int v = G[u][i];
            DFS(v);
            seg.merge(t[u].rt, t[v].rt, 1, n);
        }
    }
    //字符串从0开始
    void build(char *s) {
        init();
        for (int i = 0; s[i]; ++i) {
            extend(s[i] - 'a');
            seg.update(t[lst].rt, 1, n, i + 1);
        }
        G.clear();
        G.resize(tot + 1);
        for (int i = 1; i <= tot; ++i)
            if (t[i].fa)
                G[t[i].fa].push_back(i);
        DFS(1);
    }
    inline bool check(int u, int len, int l, int r, int c) {
        if (l + len > r)
            return 0;
        if (!t[u].nx[c])
            return 0;
        u = t[u].nx[c];
        return seg.query(t[u].rt, 1, n, l + len, r);
    }
} sam;

struct SAMT {
    //空间开两倍，节点个数是两倍字符串长度
    // maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
    // minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1
    // fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小
    // c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
    struct node {
        int maxlen, plen, fa, nx[ALP];
        node() {
            maxlen = plen = fa = 0;
            memset(nx, 0, sizeof nx);
        }
    } t[N << 2];
    int tot, lst;
    inline int newnode() {
        ++tot;
        t[tot] = node();
        return tot;
    }
    inline void init() {
        tot = 0;
        lst = newnode();
    }
    inline void extend(int id, int _plen) {
        int cur = newnode(), p;
        t[cur].maxlen = t[lst].maxlen + 1;
        t[cur].plen = _plen;
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
                t[clone].maxlen = t[p].maxlen + 1;
                for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
                t[cur].fa = t[q].fa = clone;
            }
        }
        lst = cur;
    }
    void calc() {
        ll res = 0;
        for (int i = 2; i <= tot; ++i) res += max(0, t[i].maxlen - max(t[t[i].fa].maxlen, t[i].plen));
        printf("%lld\n", res);
    }
} samt;

int main() {
    while (scanf("%s%d", s, &q) != EOF) {
        n = strlen(s);
        sam.build(s);
        for (int _q = 1; _q <= q; ++_q) {
            scanf("%s%d%d", t, &l, &r);
            samt.init();
            for (int i = 0, u = 1, len = 0; t[i]; ++i) {
                int c = t[i] - 'a';
                while (u && !sam.check(u, len, l, r, c)) {
                    if (--len <= sam.t[sam.t[u].fa].maxlen)
                        u = sam.t[u].fa;
                }
                if (!u)
                    u = 1, len = 0;
                else
                    u = sam.t[u].nx[c], ++len;
                samt.extend(c, len);
            }
            samt.calc();
        }
    }
    return 0;
}
