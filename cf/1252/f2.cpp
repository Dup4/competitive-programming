#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 4005, mod1 = 998244353, mod2 = 1e9 + 7;
vector<int> G[maxn];
int p1[maxn], p2[maxn];
struct Hash
{
    int h1, h2, len;
} d[maxn];
vector<Hash> S[maxn];
int ans = -1;
bool cmp(int a, int b)
{
    return d[a].h1 < d[b].h1 || (d[a].h1 == d[b].h1 && d[a].h2 < d[b].h2);
}
Hash merge(Hash a, Hash b)
{
    Hash jie = Hash{0, 0, a.len + b.len};
    jie.h1 = (1ll * a.h1 * p1[b.len] + b.h1) % mod1;
    jie.h2 = (1ll * a.h2 * p2[b.len] + b.h2) % mod2;
    return jie;
}
void dfs(int u, int fa)
{
    d[u] = Hash{1, 1, 1};
    for (auto v : G[u])
        if (v != fa)
            dfs(v, u);
    sort(G[u].begin(), G[u].end(), cmp);
    for (auto v : G[u])
        if (v != fa)
            d[u] = merge(d[u], d[v]);
}
void dfs2(int u, int fa)
{
    d[u] = Hash{1, 1, 1};
    sort(G[u].begin(), G[u].end(), cmp);
    Hash cat{0, 0, 0};
    int jie = 1;
    S[u].push_back(Hash{1, 1, 1});
    for (auto v : G[u])
    {
        d[u] = merge(d[u], d[v]);
        if (cat.len == 0)
            cat = d[v];
        else if (cat.h1 != d[v].h1 || cat.h2 != d[v].h2)
                jie = 0;
        S[u].push_back(d[u]);
    }
    if (jie && G[u].size() > 1)
        ans = max(ans, (int)G[u].size());
    for (int i = G[u].size() - 1; ~i; i--)
    {
        d[u] = merge(S[u][i], nvshen);
        if (G[u][i] != fa)
            dfs2(G[u][i], u);
    }
}
int main()
{
    p1[0] = p2[0] = 1;
    for (int i = 1; i < maxn; i++)
    {
        p1[i] = 1ll * p1[i - 1] * 199967 % mod1;
        p2[i] = 1ll * p2[i - 1] * 199999 % mod2;
    }
    int n, u, v;
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0);
    dfs2(1, 0);
    printf("%d\n", ans);
}
