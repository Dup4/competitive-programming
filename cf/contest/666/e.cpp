#include <bits/stdc++.h>
using namespace std;

using pII = pair<int, int>;
typedef long long ll;
#define fi first
#define se second
const int N = 5e5 + 10;
const int ALP = 26;
int n, m, q;
string s, t[N / 10];
struct qnode {
    int l, r, pl, pr, id;
    qnode(int l = 0, int r = 0, int pl = 0, int pr = 0, int id = 0) : l(l), r(r), pl(pl), pr(pr), id(id) {}
};
vector<vector<qnode>> qvec, qvec2;
pII ans[N];

struct SEG {
    struct Data {
        int v, id;
        Data() {
            v = id = 0;
        }
        Data(int v, int id) : v(v), id(id) {}
        bool operator<(const Data &other) const {
            if (v != other.v)
                return v < other.v;
            return id > other.id;
        }
    } res;
    struct node {
        int ls, rs;
        Data d;
        node(int ls = 0, int rs = 0, Data d = Data()) : ls(ls), rs(rs), d(d) {}
    } t[N * 50];
    int rt[N], tot;
    void init() {
        tot = 0;
        memset(rt, 0, sizeof rt);
        t[0] = node();
    }
    void update(int &now, int l, int r, int pos) {
        if (!now)
            now = ++tot, t[now] = node();
        if (l == r) {
            ++t[now].d.v;
            t[now].d.id = pos;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[now].ls, l, mid, pos);
        else
            update(t[now].rs, mid + 1, r, pos);
        t[now].d = max(t[t[now].ls].d, t[t[now].rs].d);
    }
    void merge(int &x, int y) {
        if (!x || !y) {
            x |= y;
            return;
        }
        if (!t[x].ls && !t[x].rs) {
            t[x].d.v += t[y].d.v;
            return;
        }
        merge(t[x].ls, t[y].ls);
        merge(t[x].rs, t[y].rs);
        t[x].d = max(t[t[x].ls].d, t[t[x].rs].d);
    }
    void query(int id, int l, int r, int ql, int qr) {
        if (!id)
            return;
        if (l >= ql && r <= qr) {
            res = max(res, t[id].d);
            return;
        }
        int mid = (l + r) >> 1;
        if (t[id].ls && ql <= mid)
            query(t[id].ls, l, mid, ql, qr);
        if (t[id].rs && qr > mid)
            query(t[id].rs, mid + 1, r, ql, qr);
    }
} seg;

struct SAM {
    //空间开两倍，节点个数是两倍字符串长度
    // maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
    // minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1
    // fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小
    // c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
    struct node {
        int maxlen, cnt, fa, nx[ALP];
        node() {
            maxlen = cnt = fa = 0;
            memset(nx, 0, sizeof nx);
        }
    } t[N << 1];
    int tot, lst, fa[22][N];
    vector<vector<int>> G;
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
        t[cur].cnt = 1;
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
                t[clone].cnt = 0;
                t[clone].maxlen = t[p].maxlen + 1;
                for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
                t[cur].fa = t[q].fa = clone;
            }
        }
        lst = cur;
    }
    inline void add(string t, int id) {
        lst = 1;
        for (int i = 0, len = (int)t.size(); i < len; ++i) {
            extend(t[i] - 'a');
            seg.update(seg.rt[lst], 1, m, id);
        }
    }
    void DFS(int u) {
        for (auto &v : G[u]) {
            DFS(v);
            seg.merge(seg.rt[u], seg.rt[v]);
        }
        for (auto &it : qvec2[u]) {
            int l = it.l, r = it.r, id = it.id;
            seg.res = SEG::Data();
            seg.query(seg.rt[u], 1, m, l, r);
            if (seg.res.v)
                ans[id] = pII(seg.res.id, seg.res.v);
        }
    }
    inline void gao() {
        G.clear();
        G.resize(tot + 10);
        qvec2.clear();
        qvec2.resize(tot + 10);
        for (int i = 1; i <= tot; ++i)
            if (t[i].fa) {
                G[t[i].fa].push_back(i);
                fa[0][i] = t[i].fa;
            }
        for (int i = 1; i <= 21; ++i)
            for (int j = 1; j <= tot; ++j) fa[i][j] = fa[i - 1][fa[i - 1][j]];
        for (int i = 1, now = 1, len = 0; i <= n; ++i) {
            int c = s[i - 1] - 'a';
            while (now && !t[now].nx[c]) {
                now = t[now].fa;
                len = t[now].maxlen;
            }
            if (!now) {
                now = 1, len = 0;
                continue;
            }
            now = t[now].nx[c];
            ++len;
            for (auto &it : qvec[i]) {
                int pl = it.pl, pr = it.pr, u = now;
                if (len < pr - pl + 1)
                    continue;
                for (int i = 21; ~i; --i)
                    if (t[fa[i][u]].maxlen >= pr - pl + 1)
                        u = fa[i][u];
                qvec2[u].push_back(it);
            }
        }
        DFS(1);
    }
} sam;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> s) {
        n = s.size();
        cin >> m;
        seg.init();
        sam.init();
        for (int i = 1; i <= m; ++i) {
            cin >> t[i];
            sam.add(t[i], i);
        }
        cin >> q;
        qvec.clear();
        qvec.resize(n + 10);
        for (int i = 1, l, r, pl, pr; i <= q; ++i) {
            cin >> l >> r >> pl >> pr;
            qvec[pr].emplace_back(l, r, pl, pr, i);
            ans[i] = pII(l, 0);
        }
        sam.gao();
        for (int i = 1; i <= q; ++i) {
            cout << ans[i].fi << " " << ans[i].se << "\n";
        }
    }
    return 0;
}
