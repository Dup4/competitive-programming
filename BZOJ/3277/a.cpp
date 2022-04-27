#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
const int ALP = 26;
int n, K;
string s[N];

struct SAM {
    //空间开两倍，节点个数是两倍字符串长度
    // maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
    // minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1
    // fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小
    // c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
    struct node {
        int maxlen, cnt, fa, nx[ALP];
        set<int> d;
        node() {
            maxlen = cnt = fa = 0;
            memset(nx, 0, sizeof nx);
            d.clear();
        }
    } t[N << 1];
    int tot, lst, c[N << 1], rk[N << 1];
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
    inline void extend(int id, int pos) {
        int cur = newnode(), p;
        t[cur].d.insert(pos);
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
    //字符串从0开始
    void build() {
        G.clear();
        G.resize(tot + 1);
        memset(c, 0, sizeof c);
        for (int i = 1; i <= tot; ++i)
            if (t[i].fa) {
                G[t[i].fa].push_back(i);
                ++c[i];
            }
        *rk = 0;
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            rk[++*rk] = u;
            for (int _ = 0, sze = (int)G[u].size(); _ < sze; ++_) {
                int v = G[u][_];
                if (--c[v] == 0)
                    q.push(v);
            }
        }
        for (int i = tot; i; --i)
            if (t[rk[i]].fa) {
                set<int>::iterator it = t[rk[i]].d.begin();
                while (it != t[rk[i]].d.end()) {
                    t[t[rk[i]].fa].d.insert(*it);
                    ++it;
                }
                t[rk[i]].cnt = t[rk[i]].d.size();
            }
    }
    void gao() {
        build();
        if (K > n) {
            for (int i = 1; i <= n; ++i) printf("0%c\n", " \n"[i == n]);
        } else {
            for (int i = 1; i <= n; ++i) {
                int now = 1;
                ll res = 0;
                for (int j = 0, len = s[i].size(); j < len; ++j) {
                    now = t[now].nx[s[i][j] - 'a'];
                    while (t[now].cnt < K) now = t[now].fa;
                    res += t[now].maxlen;
                }
                printf("%lld%c", res, " \n"[i == n]);
            }
        }
    }
} sam;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> K;
    sam.init();
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        sam.lst = 1;
        for (int j = 0, len = s[i].size(); j < len; ++j) sam.extend(s[i][j] - 'a', i);
    }
    sam.gao();
    return 0;
}
