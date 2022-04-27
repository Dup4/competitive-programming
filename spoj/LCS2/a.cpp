#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
const int ALP = 26;
char s[N];
int ans[N], f[N];

struct SAM {
    //空间开两倍
    int maxlen[N << 1], trans[N << 1][ALP], link[N << 1], sze, lst;
    vector<vector<int> > G;
    SAM() {
        sze = 0;
        lst = ++sze;
    }
    inline void init() {
        for (int i = 0; i <= sze; ++i)
            for (int j = 0; j < ALP; ++j) trans[i][j] = 0;
        sze = 0;
        lst = ++sze;
    }
    inline void extend(int id) {
        int cur = ++sze, p;
        maxlen[cur] = maxlen[lst] + 1;
        for (p = lst; p && !trans[p][id]; p = link[p]) trans[p][id] = cur;
        if (!p) {
            link[cur] = 1;
        } else {
            int q = trans[p][id];
            if (maxlen[q] == maxlen[p] + 1) {
                link[cur] = q;
            } else {
                int clone = ++sze;
                maxlen[clone] = maxlen[p] + 1;
                memcpy(trans[clone], trans[q], sizeof trans[q]);
                link[clone] = link[q];
                for (; p && trans[p][id] == q; p = link[p]) trans[p][id] = clone;
                link[cur] = link[q] = clone;
            }
        }
        lst = cur;
    }
    //字符串从0开始
    void build(char *s) {
        init();
        for (int i = 0, len = strlen(s); i < len; ++i) {
            extend(s[i] - 'a');
        }
    }
    void DFS(int u) {
        for (auto v : G[u]) {
            DFS(v);
            f[u] = max(f[u], f[v]);
        }
        ans[u] = min(ans[u], f[u]);
    }
    void gao() {
        G.clear();
        G.resize(sze + 1);
        for (int i = 1; i <= sze; ++i) {
            G[link[i]].push_back(i);
            ans[i] = maxlen[i];
        }
        while (scanf("%s", s) != EOF) {
            memset(f, 0, sizeof f);
            for (int i = 0, p = 1, cnt = 0; s[i]; ++i) {
                int c = s[i] - 'a';
                while (p && !trans[p][c]) {
                    //	cout << i << endl;
                    p = link[p];
                    cnt = maxlen[p];
                }
                if (p) {
                    ++cnt;
                    p = trans[p][c];
                } else {
                    cnt = 0;
                    p = 1;
                }
                //	cout << i << " " << cnt << " " << p << endl;
                f[p] = max(f[p], cnt);
            }
            DFS(1);
        }
        printf("%d\n", *max_element(ans + 1, ans + 1 + sze));
    }
} sam;

int main() {
    scanf("%s", s);
    sam.build(s);
    sam.gao();
    return 0;
}
