#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5e5 + 10;
const int ALP = 26;
char s[N];
int t, k;

struct SAM {
    //空间开两倍
    int maxlen[N << 1], trans[N << 1][ALP], link[N << 1], sze, lst;
    int endpos[N << 1], c[N << 1], rk[N << 1];
    ll f[N << 1];
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
        endpos[cur] = 1;
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
        memset(endpos, 0, sizeof endpos);
        for (int i = 0, len = strlen(s); i < len; ++i) {
            extend(s[i] - 'a');
        }
        memset(c, 0, sizeof c);
        for (int i = 1; i <= sze; ++i) ++c[maxlen[i]];
        for (int i = 1; i <= sze; ++i) c[i] += c[i - 1];
        for (int i = 1; i <= sze; ++i) rk[c[maxlen[i]]--] = i;
        for (int i = sze; i >= 1; --i) endpos[link[rk[i]]] += endpos[rk[i]];
    }
    void query(int u, int k) {
        if (k <= endpos[u])
            return;
        k -= endpos[u];
        for (int i = 0; i < 26; ++i)
            if (trans[u][i]) {
                if (k > f[trans[u][i]])
                    k -= f[trans[u][i]];
                else {
                    putchar('a' + i);
                    return query(trans[u][i], k);
                }
            }
    }
    void gao(int T, ll k) {
        for (int i = 1; i <= sze; ++i) {
            !T ? f[i] = endpos[i] = 1 : f[i] = endpos[i];
        }
        f[1] = endpos[1] = 0;
        for (int i = sze; i >= 1; --i) {
            for (int j = 0; j < 26; ++j) {
                if (trans[rk[i]][j]) {
                    f[rk[i]] += f[trans[rk[i]][j]];
                }
            }
        }
        if (k > f[1])
            puts("-1");
        else
            query(1, k), puts("");
    }
} sam;

int main() {
    scanf("%s", s);
    sam.build(s);
    scanf("%d%d", &t, &k);
    sam.gao(t, k);
    return 0;
}
