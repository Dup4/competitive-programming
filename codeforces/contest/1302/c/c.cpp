#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
int n, q;

struct BIT_2D {
    struct BIT {
        ll a[N];
        void init() {
            memset(a, 0, sizeof a);
        }
        void add(ll x, ll v) {
            for (; x < N; a[x] += v, x += x & -x)
                ;
        }
        ll ask(ll x) {
            ll res = 0;
            for (; x > 0; res += a[x], x -= x & -x)
                ;
            return res;
        }
    } bit1, bit2;
    void init() {
        bit1.init();
        bit2.init();
    }
    ll ask(ll x) {
        return (x + 1) * bit1.ask(x) - bit2.ask(x);
    }
    void add(ll x, ll v) {
        bit1.add(x, v);
        bit2.add(x, x * v);
    }
    ll ask(ll l, ll r) {
        return ask(r) - ask(l - 1);
    }
    void add(ll l, ll r, ll v) {
        add(l, v);
        add(r + 1, -v);
    }
} bit;

int main() {
    bit.init();
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d%d", &n, &q);
        for (int i = 1, op, x, y; i <= q; ++i) {
            scanf("%d%d%d", &op, &x, &y);
            if (op == 2)
                printf("%lld\n", bit.ask(x, y));
            else {
                ll tmp = y - bit.ask(x, x);
                bit.add(x, x, tmp);
            }
        }
    }
    return 0;
}
