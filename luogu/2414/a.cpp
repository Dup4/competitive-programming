#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second
const int N = 4e5 + 10;
const int ALP = 26;
char s[N];
int n, m, q, nd[N], res[N];
vector<vector<pii> > qvec;

struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) a[x] += v;
    }
    int query(int x) {
        int res = 0;
        for (; x; x -= x & -x) res += a[x];
        return res;
    }
    int query(int l, int r) {
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
} bit;

struct ACAM {
    struct node {
        int nx[ALP], nx2[ALP], fail, fa;
        node() {
            memset(nx, 0, sizeof nx);
            memset(nx2, 0, sizeof nx2);
            fail = fa = 0;
        }
    } t[N];
    struct Graph {
        struct node {
            int to, nx;
            node() {}
            node(int to, int nx) : to(to), nx(nx) {}
        } a[N << 1];
        int head[N], pos;
        void init() {
            pos = 0;
            memset(head, 0, sizeof head);
        }
        void add(int u, int v) {
            a[++pos] = node(v, head[u]);
            head[u] = pos;
        }
    } G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to; it; it = G.a[it].nx, v = G.a[it].to)
    int root, tot, in[N], out[N], cnt;
    int que[N], ql, qr;
    int newnode() {
        ++tot;
        t[tot] = node();
        return tot;
    }
    void init() {
        tot = 0;
        root = newnode();
    }
    int insert(int rt, int ch) {
        if (t[rt].nx[ch] == 0) {
            int tmp = newnode();
            t[rt].nx[ch] = tmp;
            t[tmp].fa = rt;
        }
        return t[rt].nx[ch];
    }
    void build() {
        ql = 1, qr = 0;
        t[root].fail = root;
        for (int i = 0; i < ALP; ++i) {
            if (t[root].nx[i] == 0) {
                t[root].nx[i] = root;
            } else {
                t[t[root].nx[i]].fail = root;
                que[++qr] = t[root].nx[i];
            }
        }
        while (ql <= qr) {
            int now = que[ql++];
            for (int i = 0; i < ALP; ++i) {
                if (t[now].nx[i] == 0) {
                    t[now].nx[i] = t[t[now].fail].nx[i];
                } else {
                    t[t[now].nx[i]].fail = t[t[now].fail].nx[i];
                    que[++qr] = t[now].nx[i];
                }
            }
        }
    }
    void buckup() {
        for (int i = 1; i <= tot; ++i)
            for (int j = 0; j < ALP; ++j) {
                t[i].nx2[j] = t[i].nx[j];
            }
    }
    void DFS(int u) {
        in[u] = ++cnt;
        erp(u) DFS(v);
        out[u] = cnt;
    }
    void gao(int u) {
        bit.update(in[u], 1);
        for (int _ = 0, sze = (int)qvec[u].size(); _ < sze; ++_) {
            pii it = qvec[u][_];
            res[it.se] = bit.query(in[it.fi], out[it.fi]);
        }
        for (int i = 0; i < ALP; ++i)
            if (t[u].nx2[i])
                gao(t[u].nx2[i]);
        bit.update(in[u], -1);
    }
    void solve() {
        G.init();
        for (int i = 2; i <= tot; ++i) {
            if (t[i].fail) {
                G.add(t[i].fail, i);
            }
        }
        cnt = 0;
        DFS(1);
        bit.init();
        gao(1);
    }
} acam;

int main() {
    acam.init();
    scanf("%s", s + 1);
    n = strlen(s + 1);
    m = 0;
    for (int i = 1, now = 1; i <= n; ++i) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            now = acam.insert(now, s[i] - 'a');
        } else if (s[i] == 'B') {
            now = acam.t[now].fa;
        } else {
            nd[++m] = now;
        }
    }
    acam.buckup();
    acam.build();
    qvec.clear();
    qvec.resize(N);
    scanf("%d", &q);
    for (int _q = 1, x, y; _q <= q; ++_q) {
        scanf("%d%d", &x, &y);
        qvec[nd[y]].push_back(pii(nd[x], _q));
    }
    acam.solve();
    for (int i = 1; i <= q; ++i) printf("%d\n", res[i]);
    return 0;
}
