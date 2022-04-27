#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5e5 + 10;
int n, q;
ll a[N];
struct BIT {
    ll a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    inline void update(int x, ll v) {
        for (; x < N; x += x & -x) a[x] += v;
    }
    inline ll query(int x) {
        ll res = 0;
        for (; x > 0; x -= x & -x) res += a[x];
        return res;
    }
    inline ll query(int l, int r) {
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
} bit;

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        bit.init();
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            bit.update(i, x);
        }
        int op, x, y;
        for (int i = 1; i <= q; ++i) {
            scanf("%d%d%d", &op, &x, &y);
            if (op == 1) {
                bit.update(x, y);
            } else {
                printf("%lld\n", bit.query(x, y));
            }
        }
    }
    return 0;
}
