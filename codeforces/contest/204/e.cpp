#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
const int ALP = 26;
int T, k;
char s[N];

struct SAM {
    struct node {
        int maxlen, cnt, fa, nx[ALP];
        node() {
            maxlen = cnt = fa = 0;
            memset(nx, 0, sizeof nx);
        }
    } t[N << 1];
    int tot, lst, c[N << 1], rk[N << 1];
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
    //字符串从0开始
    void build(char *s) {
        init();
        for (int i = 0; s[i]; ++i) {
            extend(s[i] - 'a');
        }
        memset(c, 0, sizeof c);
        for (int i = 1; i <= tot; ++i) c[t[i].maxlen]++;
        for (int i = 1; i <= tot; ++i) c[i] += c[i - 1];
        for (int i = 1; i <= tot; ++i) rk[c[t[i].maxlen]--] = i;
        for (int i = tot; i; --i) t[t[rk[i]].fa].cnt += t[rk[i]].cnt;
    }
    void gao() {
        ll res = 0;
        for (int i = 1; i <= tot; ++i)
            if (t[i].cnt >= k) {
                res += t[i].maxlen - t[t[i].fa].maxlen;
            }
        printf("%lld", res);
    }
} sam;

int main() {
    while (scanf("%d%d", &T, &k) != EOF) {
        for (int i = 1; i <= T; ++i) {
            scanf("%s", s);
            sam.build(s);
            sam.gao();
            putchar(" \n"[i == T]);
        }
    }
    return 0;
}
