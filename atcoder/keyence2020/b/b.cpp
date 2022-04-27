#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 2e5 + 10;
int n, m, b[N];
pII a[N];

struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) {
            a[x] = max(a[x], v);
        }
    }
    int query(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) res = max(res, a[x]);
        return res;
    }
} bit;

int main() {
    while (scanf("%d", &n) != EOF) {
        m = 0;
        for (int i = 1, x, l; i <= n; ++i) {
            scanf("%d%d", &x, &l);
            a[i].fi = x - l + 1;
            a[i].se = x + l - 1;
            b[++m] = a[i].fi;
            b[++m] = a[i].se;
        }
        bit.init();
        sort(b + 1, b + 1 + m);
        m = unique(b + 1, b + 1 + m) - b - 1;
        for (int i = 1; i <= n; ++i) {
            a[i].fi = lower_bound(b + 1, b + 1 + m, a[i].fi) - b;
            a[i].se = lower_bound(b + 1, b + 1 + m, a[i].se) - b;
        }
        sort(a + 1, a + 1 + n, [&](pII x, pII y) {
            return x.fi < y.fi;
        });
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            int now = bit.query(a[i].fi - 1) + 1;
            res = max(res, now);
            bit.update(a[i].se, now);
        }
        cout << res << endl;
    }
    return 0;
}
