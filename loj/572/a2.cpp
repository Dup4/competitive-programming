#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
#define ll long long
#define uint unsigned int
#define MAX 100000
int K, blk;
uint n;
int w[MAX], id1[MAX], id2[MAX], m;
int pri[MAX], tot;
bool zs[MAX];
uint g[MAX], prik[MAX];
uint fpow(uint a, int b) {
    uint s = 1;
    while (b) {
        if (b & 1)
            s *= a;
        a *= a;
        b >>= 1;
    }
    return s;
}
int getid(int x) {
    return (x <= blk) ? id1[x] : id2[n / x];
}
void pre(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!zs[i])
            pri[++tot] = i, prik[tot] = fpow(i, K);
        ;
        for (int j = 1; j <= tot && i * pri[j] <= n; ++j) {
            zs[i * pri[j]] = true;
            if (i % pri[j] == 0)
                break;
        }
    }
}
uint calc(int x, int y) {
    if (x <= 1 || pri[y] > x)
        return 0;
    uint ret = (g[getid(x)] - y + 1) * prik[y - 1];
    for (int i = y; i <= tot && 1ll * pri[i] * pri[i] <= x; ++i) {
        ll t1 = pri[i], t2 = 1ll * pri[i] * pri[i];
        for (int e = 1; t2 <= x; ++e, t1 = t2, t2 *= pri[i]) ret += calc(x / t1, i + 1) + prik[i];
    }
    return ret;
}
uint M[MAX];
bool vis[MAX];
uint S(int n) {
    if (vis[getid(n)])
        return M[getid(n)];
    uint ret = calc(n, 1) + g[getid(n)];
    for (int i = 2, j; i <= n; i = j + 1) j = n / (n / i), ret -= (j - i + 1) * S(n / i);
    vis[getid(n)] = true;
    return M[getid(n)] = ret;
}
int main() {
    scanf("%u%d", &n, &K);
    pre(blk = sqrt(n));
    for (uint i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        w[++m] = n / i;
        g[m] = w[m] - 1;
        if (w[m] <= blk)
            id1[w[m]] = m;
        else
            id2[n / w[m]] = m;
    }
    for (int j = 1; j <= tot && 1ll * pri[j] * pri[j] <= n; ++j)
        for (int i = 1; i <= m && 1ll * pri[j] * pri[j] <= w[i]; ++i) g[i] -= g[getid(w[i] / pri[j])] - (j - 1);
    uint ans = 0, lt = 0, nw;
    for (uint i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        nw = S(j);
        cout << nw << endl;
        ans += (uint)1 * (n / i) * (n / i) * (nw - lt);
        lt = nw;
    }
    printf("%u\n", ans);
    return 0;
}
