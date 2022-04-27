#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
const int ALP = 26;
int n;
char s[N];
ll ans[N];

struct SAM {
    //空间开两倍，节点个数是两倍字符串长度
    // maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
    // minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1
    // fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小
    // c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
    struct node {
        int maxlen, pos, fa, nx[ALP];
        node() {
            maxlen = pos = fa = 0;
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
    inline void extend(int id, int _pos) {
        int cur = newnode(), p;
        t[cur].maxlen = t[lst].maxlen + 1;
        t[cur].pos = _pos;
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
    //字符串从0开始
    void add(char *s, int pos) {
        for (int i = 0; s[i]; ++i) {
            extend(s[i] - 'a', pos);
        }
    }
    void DFS(int u) {
        for (int i = 0, sze = (int)G[u].size(); i < sze; ++i) DFS(G[u][i]);
        for (int i = 0, sze = (int)G[u].size(), v; i < sze; ++i) {
            v = G[u][i];
            if (t[v].pos == -1) {
                t[u].pos = -1;
                break;
            }
            if (!t[v].pos)
                continue;
            if (!t[u].pos)
                t[u].pos = t[v].pos;
            else if (t[u].pos != t[v].pos) {
                t[u].pos = -1;
                break;
            }
        }
    }
    void work() {
        G.clear();
        G.resize(tot + 1);
        for (int i = 2; i <= tot; ++i) G[t[i].fa].push_back(i);
        //	for (int i = 1; i <= tot; ++i) cout << i << " " << t[i].pos << endl;
        DFS(1);
        memset(ans, 0, sizeof ans);
        for (int u = 1; u <= tot; ++u) {
            if (t[u].pos != -1) {
                ans[t[u].pos] += t[u].maxlen - t[t[u].fa].maxlen;
            }
        }
    }
} sam;

int main() {
    while (scanf("%d", &n) != EOF) {
        sam.init();
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s);
            sam.lst = 1;
            sam.add(s, i);
        }
        sam.work();
        for (int i = 1; i <= n; ++i) printf("%lld\n", ans[i]);
    }
    return 0;
}
