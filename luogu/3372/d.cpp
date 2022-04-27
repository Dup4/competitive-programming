#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
int n, m;
ll a[N];

struct BIT {
    ll a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, ll v) {
        for (; x < N; a[x] += v, x += x & -x)
            ;
    }
    ll query(int x) {
        ll res = 0;
        for (; x; res += a[x], x -= x & -x)
            ;
        return res;
    }
};

struct BIT2 {
    BIT bit[2];
    void init() {
        bit[0].init();
        bit[1].init();
    }
    void update(int x, ll v) {
        bit[0].update(x, v);
        bit[1].update(x, v * x);
    }
    ll query(int x) {
        return bit[0].query(x) * (x + 1) - bit[1].query(x);
    }
    void update(int l, int r, ll v) {
        update(l, v);
        update(r + 1, -v);
    }
    ll query(int l, int r) {
        return query(r) - query(l - 1);
    }
} bit;

int main() {
    scanf("%d%d", &n, &m);
    bit.init();
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i), bit.update(i, i, a[i]);
    for (int i = 1, op, x, y; i <= m; ++i) {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            ll k;
            scanf("%lld", &k);
            bit.update(x, y, k);
        } else {
            printf("%lld\n", bit.query(x, y));
        }
    }

    return 0;
}
