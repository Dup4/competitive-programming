#include <bits/stdc++.h>
using namespace std;
#define db double
#define N 2010
#define ALP 10
const db eps = 1e-5;
char s[N], t[N], res[N];
int n, m;

struct ACAM {
    struct node {
        int nx[ALP], fail;
        db w;
        int cnt;
        node() {
            memset(nx, -1, sizeof nx);
            w = cnt = 0;
        }
    } t[N];
    struct fnode {
        db v;
        int pre;
        char c;
        fnode() {
            v = -1e9;
            pre = c = 0;
        }
        fnode(db v, int pre, char c) : v(v), pre(pre), c(c) {}
    } f[N][N];
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
    void insert(char *s, int x) {
        int len = strlen(s);
        int now = root;
        for (int i = 0; i < len; ++i) {
            if (t[now].nx[s[i] - '0'] == -1)
                t[now].nx[s[i] - '0'] = newnode();
            now = t[now].nx[s[i] - '0'];
        }
        //表示以该结点结尾的模式串数量
        t[now].w = log(x);
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
            t[now].w += t[t[now].fail].w;
            t[now].cnt += t[t[now].fail].cnt;
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
    bool check(char *s, db x) {
        int len = strlen(s + 1);
        for (int i = 1; i <= tot; ++i) {
            t[i].w -= x * t[i].cnt;
        }
        for (int i = 0; i <= len; ++i) {
            for (int j = 1; j <= tot; ++j) {
                f[i][j] = fnode();
            }
        }
        f[0][1] = fnode(0, -1, 0);
        for (int i = 0; i < len; ++i) {
            for (int j = 1; j <= tot; ++j) {
                if (s[i + 1] == '.') {
                    for (int k = 0; k < ALP; ++k) {
                        int nx = t[j].nx[k];
                        if (f[i + 1][nx].v < f[i][j].v + t[nx].w) {
                            f[i + 1][nx] = fnode(f[i][j].v + t[nx].w, j, k + '0');
                        }
                    }
                } else {
                    int nx = t[j].nx[s[i + 1] - '0'];
                    if (f[i + 1][nx].v < f[i][j].v + t[nx].w) {
                        f[i + 1][nx] = fnode(f[i][j].v + t[nx].w, j, s[i + 1]);
                    }
                }
            }
        }
        db ans = -1e9;
        for (int i = 1; i <= tot; ++i) ans = max(ans, f[len][i].v);
        for (int i = 1; i <= tot; ++i) t[i].w += x * t[i].cnt;
        return ans > 0;
    }
    void out(int n) {
        int it;
        db Max = -1e9;
        for (int i = 1; i <= tot; ++i) {
            if (f[n][i].v > 0) {
                it = i;
                break;
                Max = f[n][i].v;
            }
        }
        for (int i = n; i >= 1; --i) {
            res[i] = f[i][it].c;
            it = f[i][it].pre;
        }
        res[n + 1] = 0;
        printf("%s\n", res + 1);
    }
} ac;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        scanf("%s", s + 1);
        ac.init();
        for (int i = 1, v; i <= m; ++i) {
            scanf("%s%d", t, &v);
            ac.insert(t, v);
        }
        ac.build();
        db l = 0, r = 25, res = 0;
        while (r - l > eps) {
            db mid = (l + r) / 2;
            if (ac.check(s, mid)) {
                res = mid;
                l = mid;
            } else {
                r = mid;
            }
        }
        ac.check(s, res);
        ac.out(strlen(s + 1));
    }
    return 0;
}
