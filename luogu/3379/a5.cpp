#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 10;
int n, m, st;
struct Edge {
    int next, to;
} e[MAXN << 1];
int ecnt, head[MAXN];
void add(int x, int y) {
    e[++ecnt].next = head[x];
    e[ecnt].to = y;
    head[x] = ecnt;
}

int appear[MAXN], elm[MAXN], dep[MAXN], tot;
void dfs(int x, int pre) {
    appear[x] = ++tot;
    elm[tot] = x;
    dep[tot] = dep[appear[pre]] + 1;
    for (int i = head[x]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == pre)
            continue;
        dfs(v, x);
        elm[++tot] = x;
        dep[tot] = dep[appear[x]];
    }
}

int blockLen, num, L[MAXN], R[MAXN], bl[MAXN];
int blockTyp[MAXN], f[MAXN][32], g[MAXN][32];
int lookUp[MAXN];
inline int computeType(int x) {
    int sum = 0;
    for (int i = L[x]; i <= R[x] - 1; i++) sum <<= 1, sum += (dep[i + 1] > dep[i]);
    return sum;
}

inline void calcPos(int x) {
    int len = 0, po = 0, cnt = 0, mn = 1 << 30, mnid;
    len = blockLen;
    for (int i = len; i >= 0; i--) {
        po++;
        if ((1 << i) & x)
            cnt++;
        else
            cnt--;
        if (cnt < mn)
            mn = cnt, mnid = po;
    }
    lookUp[x] = mnid - 1;
}

void build() {
    blockLen = log2(tot) / 2;
    num = tot / blockLen;
    if (tot % blockLen)
        num++;
    for (int i = 1; i <= num; i++) {
        L[i] = (i - 1) * blockLen + 1;
        R[i] = i * blockLen;
    }
    for (int i = tot + 1; i <= R[num]; i++) dep[i] = (1 << 30);
    for (int i = 1; i <= tot; i++) bl[i] = (i - 1) / blockLen + 1;
    for (int i = 0; i * i <= tot; i++) calcPos(i);
    for (int i = 1; i <= num; i++) blockTyp[i] = computeType(i);
    for (int i = 1; i <= num; i++)
        g[i][0] = (i - 1) * blockLen + lookUp[blockTyp[i]], f[i][0] = dep[g[i][0]];  // offset!
    for (int j = 1; (1 << j) <= num; j++)
        for (int i = 1; i <= num; i++)
            if (f[i][j - 1] < f[i + (1 << (j - 1))][j - 1])
                f[i][j] = f[i][j - 1], g[i][j] = g[i][j - 1];
            else
                f[i][j] = f[i + (1 << (j - 1))][j - 1], g[i][j] = g[i + (1 << (j - 1))][j - 1];
}

int inBlockQuery(int x, int y) {
    int u = blockTyp[bl[x]], v = (bl[x] - 1) * blockLen + lookUp[u];
    if (x <= v && v <= y)
        return v;
    int sav = bl[x];
    x -= L[sav] - 1;
    y -= L[sav] - 1;
    u >>= (blockLen - y);
    u &= (~((-1) << (y - x)));
    return (sav - 1) * blockLen + lookUp[u] - (blockLen - y);
}

int query(int x, int y) {
    if (bl[x] == bl[y])
        return inBlockQuery(x, y);
    int mn = 1 << 30, mnid, tmp;
    tmp = inBlockQuery(x, R[bl[x]]);
    if (dep[tmp] < mn)
        mn = dep[tmp], mnid = tmp;
    tmp = inBlockQuery(L[bl[y]], y);
    if (dep[tmp] < mn)
        mn = dep[tmp], mnid = tmp;
    int l = bl[x] + 1, r = bl[y] - 1, len;
    if ((r - l + 1 > 0))
        len = log2(r - l + 1);
    else
        return mnid;
    if (f[l][len] < mn)
        mn = f[l][len], mnid = g[l][len];
    if (f[r - (1 << len) + 1][len] < mn)
        mn = f[r - (1 << len) + 1][len], mnid = g[r - (1 << len) + 1][len];
    return mnid;
}

int main() {
    scanf("%d%d%d", &n, &m, &st);
    int x, y;
    for (int i = 1; i <= n - 1; i++) {
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dfs(st, 0);
    build();
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        if (appear[x] > appear[y])
            swap(x, y);
        printf("%d\n", elm[query(appear[x], appear[y])]);
    }
    return 0;
}
