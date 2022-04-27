#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ui = unsigned int;
namespace IO {
const int S = (1 << 25) + 5;
// Input Correlation
char buf[S], *H, *T;
inline char Get() {
    if (H == T)
        T = (H = buf) + fread(buf, 1, S, stdin);
    if (H == T)
        return -1;
    return *H++;
}
template <class T>
inline void read(T &x) {
    x = 0;
    int fg = 1;
    char c = Get();
    while (!isdigit(c) && c != '-') c = Get();
    if (c == '-')
        fg = -1, c = Get();
    while (isdigit(c)) x = x * 10 + c - '0', c = Get();
    x *= fg;
}
inline void reads(char *s) {
    char c = Get();
    int tot = 0;
    while (c < 'a' || c > 'z') c = Get();
    while (c >= 'a' && c <= 'z') s[++tot] = c, c = Get();
    s[++tot] = '\0';
}
// Output Correlation
char obuf[S], *oS = obuf, *oT = oS + S - 1, c, qu[55];
int qr;
inline void flush() {
    fwrite(obuf, 1, oS - obuf, stdout);
    oS = obuf;
}
inline void putc(char x) {
    *oS++ = x;
    if (oS == oT)
        flush();
}
template <class I>
inline void print(I x) {
    if (!x)
        putc('0');
    if (x < 0)
        putc('-'), x = -x;
    while (x) qu[++qr] = x % 10 + '0', x /= 10;
    while (qr) putc(qu[qr--]);
}
inline void prints(const char *s) {
    int len = strlen(s);
    for (int i = 0; i < len; i++) putc(s[i]);
    putc('\n');
}
inline void printd(int d, double x) {
    long long t = (long long)floor(x);
    print(t);
    putc('.');
    x -= t;
    while (d--) {
        double y = x * 10;
        x *= 10;
        int c = (int)floor(y);
        putc(c + '0');
        x -= floor(y);
    }
}
}  // namespace IO
using namespace IO;
const int N = 1e6 + 10;
int n, q;
ui p[N];
ll ans[5010];
vector<vector<int>> G;
int fa[N], deep[N];
struct node {
    int k, id, f;
};
vector<vector<node>> qvec;
struct BIT {
    ll a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    inline void update(int x, ll v) {
        for (; x <= n; x += x & -x) a[x] += v;
    }
    inline ll query(int x) {
        ll res = 0;
        for (; x > 0; x -= x & -x) res += a[x];
        return res;
    }
    inline ll query(int l, int r) {
        r = min(r, n);
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
} bit;
void pre(int u) {
    for (auto &v : G[u])
        if (v != fa[u]) {
            deep[v] = deep[u] + 1;
            fa[v] = u;
            pre(v);
        }
}
void DFS(int u) {
    for (auto &it : qvec[u]) ans[it.id] -= bit.query(deep[u], deep[u] + it.k) * it.f;
    bit.update(deep[u], p[u]);
    for (auto &v : G[u])
        if (v != fa[u])
            DFS(v);
    for (auto &it : qvec[u]) ans[it.id] += bit.query(deep[u], deep[u] + it.k) * it.f;
}

int main() {
    read(n);
    for (int i = 1; i <= n; ++i) read(p[i]);
    G.clear();
    G.resize(n + 1);
    qvec.clear();
    qvec.resize(n + 1);
    for (int i = 1, u, v; i < n; ++i) {
        read(u);
        read(v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    read(q);
    fa[1] = 0;
    deep[1] = 1;
    pre(1);
    for (int i = 1, u, k; i <= q; ++i) {
        read(u);
        read(k);
        qvec[u].push_back({k, i, 1});
        int v = u;
        while (fa[v] && k) {
            --k;
            qvec[fa[v]].push_back({k, i, 1});
            if (k - 1 >= 0)
                qvec[v].push_back({k - 1, i, -1});
            v = fa[v];
        }
    }
    memset(ans, 0, sizeof ans);
    bit.init();
    DFS(1);
    for (int i = 1; i <= q; ++i) print(ans[i]), putc('\n');
    flush();
    return 0;
}
