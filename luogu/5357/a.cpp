#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, M = 2e6 + 10, ALP = 26;
int n, acamPos[N];
char s[M], t[N];

struct ACAM {
    struct node {
        int nx[ALP], fail;
        int cnt, num;
        void init() {
            memset(nx, -1, sizeof nx);
            cnt = num = 0;
        }
    } t[N];
    vector<vector<int>> G;
    int root, tot;
    int que[N], ql, qr;
    int newnode() {
        ++tot;
        t[tot].init();
        return tot;
    }
    void init() {
        tot = 0;
        root = newnode();
    }
    // 0-index
    int insert(char *s) {
        int now = root;
        for (int i = 0; s[i]; ++i) {
            if (t[now].nx[s[i] - 'a'] == -1)
                t[now].nx[s[i] - 'a'] = newnode();
            now = t[now].nx[s[i] - 'a'];
        }
        ++t[now].cnt;
        return now;
    }
    void build() {
        ql = 1, qr = 0;
        t[root].fail = root;
        //将第二层出现过的字母扔进队列，并将fail指向根
        //对于没出现过的字母，直接将该字母的下一个节点指向根
        for (int i = 0; i < ALP; ++i) {
            if (t[root].nx[i] == -1) {
                t[root].nx[i] = root;
            } else {
                t[t[root].nx[i]].fail = root;
                que[++qr] = t[root].nx[i];
            }
        }
        while (ql <= qr) {
            int now = que[ql++];
            for (int i = 0; i < ALP; ++i) {
                //如果当前节点没有子节点i + 'a'
                //则让这个子节点指向当前节点fail指针对应的子节点
                if (t[now].nx[i] == -1) {
                    t[now].nx[i] = t[t[now].fail].nx[i];
                } else {
                    //如果当前节点有子节点i + 'a'
                    //则让这个子节点的fail指针指向(((它父亲节点)的fail指针指向的那个节点)的对应的子节点)
                    t[t[now].nx[i]].fail = t[t[now].fail].nx[i];
                    que[++qr] = t[now].nx[i];
                }
            }
        }
    }
    void dfs(int u) {
        for (auto v : G[u]) {
            dfs(v);
            t[u].num += t[v].num;
        }
    }
    void gao(char *s) {
        int now = root;
        for (int i = 0; s[i]; ++i) {
            now = t[now].nx[s[i] - 'a'];
            ++t[now].num;
        }
        G.clear();
        G.resize(tot + 5);
        for (int i = 2; i <= tot; ++i) {
            G[t[i].fail].push_back(i);
        }
        dfs(1);
    }
} acam;

int main() {
    scanf("%d", &n);
    acam.init();
    for (int i = 1; i <= n; ++i) {
        scanf("%s", t);
        acamPos[i] = acam.insert(t);
    }
    acam.build();
    scanf("%s", s);
    acam.gao(s);
    for (int i = 1; i <= n; ++i) printf("%d\n", acam.t[acamPos[i]].num);
    return 0;
}
