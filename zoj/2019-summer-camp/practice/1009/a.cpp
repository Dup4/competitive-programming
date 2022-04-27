#include <bits/stdc++.h>
using namespace std;

#define N 110
#define ll long long
const ll p = 1e9 + 7;
ll d;
int n, lc[N], rc[N];
ll ans[N];
void add(ll &x, ll y) {
    x += y;
    if (x >= p)
        x -= p;
}
struct node {
    ll a[N][N];
    node() {
        memset(a, 0, sizeof a);
    }
    node operator*(const node &other) const {
        node res = node();
        for (int i = 1; i <= n + n; ++i) {
            for (int j = 1; j <= n + n; ++j) {
                for (int k = 1; k <= n + n; ++k) {
                    add(res.a[i][j], a[i][k] * other.a[k][j] % p);
                }
            }
        }
        return res;
    }
} base, res;
void qmod(node &res, node base, ll n) {
    while (n) {
        if (n & 1) {
            res = res * base;
        }
        base = base * base;
        n >>= 1;
    }
}

void init() {
    memset(ans, 0, sizeof ans);
    base = node();
    res = node();
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        init();
        scanf("%lld%d", &d, &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", lc + i);
            ++base.a[i][lc[i]];
            ++base.a[i][lc[i] + n];
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", rc + i);
            ++base.a[i][rc[i]];
            ++base.a[i][rc[i] + n];
        }
        for (int i = 1; i <= n; ++i) {
            base.a[i + n][i + n] = 1;
        }
        for (int i = 1; i <= n; ++i) res.a[i][i] = 1, res.a[i][i + n] = 1;
        qmod(res, base, d);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                add(ans[i], res.a[j][i + n]);
            }
        }
        for (int i = 1; i <= n; ++i) {
            printf("%lld%c", ans[i], " \n"[i == n]);
        }
    }
    return 0;
}
