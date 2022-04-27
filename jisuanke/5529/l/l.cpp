#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10, ALP = 26, M = 20;
int n, q, trie_pos[N];
char s[N];
struct SAM {
    struct node {
        int maxlen, cnt, fa, nx[ALP];
        void init() {
            maxlen = cnt = fa = 0;
            memset(nx, 0, sizeof nx);
        }
    } t[N << 1];
    int tot, c[N << 1], rk[N << 1], fa[N << 1][M];
    vector<vector<int>> G;
    int newnode() {
        ++tot;
        t[tot].init();
        return tot;
    }
    void init() {
        tot = 0;
        newnode();
    }
    int extend(int id, int lst, int cnt) {
        int cur = newnode(), p;
        t[cur].cnt = cnt;
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
        return cur;
    }
    void dfs(int u) {
        for (int i = 1; i < M; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for (auto &v : G[u]) {
            fa[v][0] = u;
            dfs(v);
            t[u].cnt += t[v].cnt;
        }
    }
    void build() {
        memset(c, 0, sizeof c);
        for (int i = 1; i <= tot; ++i) c[t[i].maxlen]++;
        for (int i = 1; i <= tot; ++i) c[i] += c[i - 1];
        //		for (int i = 1; i <= tot; ++i) rk[c[t[i].maxlen]--] = i;
        //		for (int i = tot; i; --i) t[t[rk[i]].fa].cnt += t[rk[i]].cnt;
        G.clear();
        G.resize(tot + 1);
        for (int i = 1; i <= tot; ++i) {
            if (t[i].fa) {
                G[t[i].fa].push_back(i);
            }
        }
        fa[1][0] = 0;
        dfs(1);
    }
    int query(int x, int len) {
        for (int i = M - 1; i >= 0; --i) {
            if (t[fa[x][i]].maxlen >= len) {
                x = fa[x][i];
            }
        }
        return t[x].cnt;
    }
} sam;

vector<vector<int>> G;
struct Trie {
    struct node {
        int nx[ALP], cnt, sam_pos;
        void init() {
            memset(nx, 0, sizeof nx);
            cnt = 0;
            sam_pos = 0;
        }
    } t[N];
    int rt, tot;
    int newnode() {
        ++tot;
        t[tot].init();
        return tot;
    }
    void init() {
        tot = 0;
        rt = newnode();
    }
    int add(int p, int ch) {
        if (!t[p].nx[ch]) {
            t[p].nx[ch] = newnode();
        }
        int now = t[p].nx[ch];
        ++t[now].cnt;
        return now;
    }
    void dfs(int u) {
        for (auto &v : G[u]) {
            trie_pos[v] = add(trie_pos[u], s[v] - 'A');
            dfs(v);
        }
    }
    void bfs() {
        queue<int> q;
        q.push(1);
        t[1].sam_pos = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < ALP; ++i) {
                if (!t[u].nx[i])
                    continue;
                int now = t[u].nx[i];
                t[now].sam_pos = sam.extend(i, t[u].sam_pos, t[now].cnt);
                q.push(now);
            }
        }
    }
} trie;

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        G.clear();
        G.resize(n + 1);
        scanf("%s", s + 1);
        trie.init();
        trie_pos[0] = 1;
        trie_pos[1] = trie.add(trie_pos[0], s[1] - 'A');
        for (int u = 2, v; u <= n; ++u) {
            scanf("%d", &v);
            G[v].push_back(u);
        }
        trie.dfs(1);
        sam.init();
        trie.bfs();
        sam.build();
        int x, len;
        while (q--) {
            scanf("%d%d", &x, &len);
            printf("%d\n", sam.query(trie.t[trie_pos[x]].sam_pos, len));
        }
    }
    return 0;
}
