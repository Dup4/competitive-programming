#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, k, a[N], w[N], vis[N];
ll tt[2][N], *f = tt[0], *g = tt[1];
void gao(int l, int r, int kl, int kr, ll W) {
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    int p = mid < kr ? mid : kr;
    int k = kr;
    for (int i = l; i <= mid; ++i) W += w[a[i]]++;
    for (int i = kl; i <= p; ++i) {
        W -= --w[a[i]];
        if (f[mid] > W + g[i]) {
            f[mid] = W + g[i];
            k = i;
        }
    }
    vis[mid] = k;
    for (int i = kl; i <= p; ++i) W += w[a[i]]++;
    for (int i = l; i <= mid; ++i) W -= --w[a[i]];
    gao(l, mid - 1, kl, k, W);
    for (int i = l; i <= mid; ++i) W += w[a[i]]++;
    for (int i = kl; i < k; ++i) W -= --w[a[i]];
    gao(mid + 1, r, k, kr, W);
    for (int i = kl; i < k; ++i) W += w[a[i]]++;
    for (int i = l; i <= mid; ++i) W -= --w[a[i]];
}

int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        memset(w, 0, sizeof w);
        g[0] = 0;
        for (int i = 1; i <= n; ++i) {
            g[i] = g[i - 1] + w[a[i]];
            ++w[a[i]];
        }
        memset(w, 0, sizeof w);
        while (--k) {
            memset(f, 0x3f, sizeof tt[0]);
            gao(1, n, 1, n, 0);
            swap(f, g);
        }
        printf("%lld\n", g[n]);
    }
    return 0;
}
