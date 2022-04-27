#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
const int ALP = 26;
const int mod = 998244353;
int _T, len, K, n, q, a[110], f[N], res;
char s[N];
inline ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
inline void add(int &x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
}

struct SAM {
    //空间开两倍，节点个数是两倍字符串长度
    // maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
    // minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1
    // fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小
    // c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
    // pos表示那个结点在字符串的endpos的最小值，即firstpos
    struct node {
        int maxlen, fa, nx[ALP];
        node() {
            maxlen = fa = 0;
            memset(nx, 0, sizeof nx);
        }
    } t[N << 1];
    int tot, lst;
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
                t[clone].maxlen = t[p].maxlen + 1;
                for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
                t[cur].fa = t[q].fa = clone;
            }
        }
        lst = cur;
        add(res, (f[t[lst].maxlen] - f[t[t[lst].fa].maxlen] + mod) % mod);
    }
    //字符串从0开始
    void build(char *s) {
        init();
        for (int i = 0; s[i]; ++i) {
            extend(s[i] - 'a');
        }
    }
} sam;

int main() {
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d%d%d", &len, &K, &n, &q);
        ll inv = qpow(26, n);
        inv = qpow(inv, mod - 2);
        scanf("%s", s);
        for (int i = 0; i <= K; ++i) scanf("%d", a + i);
        f[0] = 0;
        for (int i = 1; i <= len + q; ++i) {
            if (i > n) {
                f[i] = f[i - 1];
                continue;
            }
            ll t = 1;
            f[i] = 0;
            for (int j = 0; j <= K; ++j) {
                add(f[i], t * a[j] % mod);
                t = t * i % mod;
            }
            f[i] = 1ll * (n - i + 1) % mod * qpow(26, n - i) % mod * f[i] % mod;
            add(f[i], f[i - 1]);
        }
        res = 0;
        sam.build(s);
        printf("%lld\n", inv * res % mod);
        char c[10];
        for (int i = 1; i <= q; ++i) {
            scanf("%s", c);
            sam.extend(c[0] - 'a');
            printf("%lld\n", inv * res % mod);
        }
    }
    return 0;
}
