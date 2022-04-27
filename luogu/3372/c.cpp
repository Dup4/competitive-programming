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
    void add(int x, ll v) {
        for (; x < N; a[x] += v, x += x & -x)
            ;
    }
    ll ask(int x) {
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
    ll ask(int x) {
        return bit[0].ask(x) * (x + 1) - bit[1].ask(x);
    }
    void add(int x, ll v) {
        bit[0].add(x, v);
        bit[1].add(x, v * x);
    }
    ll ask(int l, int r) {
        return ask(r) - ask(l - 1);
    }
    void add(int l, int r, ll v) {
        add(l, v);
        add(r + 1, -v);
    }
} bit;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        bit.init();
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", a + i);
            bit.add(i, i, a[i]);
        }
        for (int i = 1, op, x, y; i <= m; ++i) {
            ll k;
            scanf("%d%d%d", &op, &x, &y);
            if (op == 1) {
                scanf("%lld", &k);
                bit.add(x, y, k);
            } else {
                printf("%lld\n", bit.ask(x, y));
            }
        }
    }
    return 0;
}
