#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 2010
#define ALP 10
const ll p = 1e9 + 7;
char s[N], t[N];
int m;
int f[N][N], g[N][N][2];

struct ACAM {
    struct node {
        int nx[ALP], fail;
        int cnt;
        node() {
            memset(nx, -1, sizeof nx);
            cnt = 0;
        }
    } t[N];
    int root, tot;
    int que[N], ql, qr;
    //节点从1开始
    int newnode() {
        ++tot;
        t[tot] = node();
        return tot;
    }
    void init() {
        tot = 0;
        root = newnode();
    }
    void insert(char *s) {
        int len = strlen(s);
        int now = root;
        for (int i = 0; i < len; ++i) {
            if (t[now].nx[s[i] - '0'] == -1)
                t[now].nx[s[i] - '0'] = newnode();
            now = t[now].nx[s[i] - '0'];
        }
        //表示以该结点结尾的模式串数量
        t[now].cnt = 1;
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
            t[now].cnt |= t[t[now].fail].cnt;
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
    int gao(char *s) {
        int n = strlen(s + 1);
        // f[i][j]表示前i位，状态为j的方案数
        f[0][1] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= tot; ++j) {
                if (t[j].cnt)
                    continue;
                for (int k = 0; k < ALP; ++k) {
                    if (i == 0 && k == 0)
                        continue;
                    if (t[t[j].nx[k]].cnt == 0) {
                        (f[i + 1][t[j].nx[k]] += f[i][j]) %= p;
                    }
                }
            }
        }
        int res = 0;
        for (int i = 1; i < n; ++i)
            for (int j = 1; j <= tot; ++j) (res += f[i][j]) %= p;
        // g[i][j][k] 表示前i位，状态为j，是否卡住n的前i位的方案数(0没有卡住，1卡住)
        g[0][1][1] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= tot; ++j) {
                if (t[j].cnt)
                    continue;
                for (int k = 0; k < ALP; ++k) {
                    if (i == 0 && k == 0)
                        continue;
                    if (t[t[j].nx[k]].cnt == 0) {
                        (g[i + 1][t[j].nx[k]][0] += g[i][j][0]) %= p;
                        if (k < s[i + 1] - '0') {
                            (g[i + 1][t[j].nx[k]][0] += g[i][j][1]) %= p;
                        }
                        if (k == s[i + 1] - '0') {
                            (g[i + 1][t[j].nx[k]][1] += g[i][j][1]) %= p;
                        }
                    }
                }
            }
        }
        for (int i = 1; i <= tot; ++i) {
            (res += g[n][i][0]) %= p;
            (res += g[n][i][1]) %= p;
        }
        return res;
    }
} ac;

int main() {
    ac.init();
    scanf("%s%d", s + 1, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%s", t);
        ac.insert(t);
    }
    ac.build();
    printf("%d\n", ac.gao(s));
    return 0;
}
