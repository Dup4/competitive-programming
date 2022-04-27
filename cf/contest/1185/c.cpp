#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
#define pll pair<ll, ll>
#define fi first
#define se second
int n, M;
int t[N];

struct SEG {
    ll a[N], b[N];
    void init() {
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
    }
    void update(int id, int l, int r, int x) {
        if (l == r) {
            a[id] += l;
            b[id] += 1;
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(id << 1, l, mid, x);
        else
            update(id << 1 | 1, mid + 1, r, x);
        a[id] = a[id << 1] + a[id << 1 | 1];
        b[id] = b[id << 1] + b[id << 1 | 1];
    }
    ll query(int id, int l, int r, ll k) {
        if (l == r) {
            return min(b[id], k / l);
        }
        int mid = (l + r) >> 1;
        if (k <= a[id << 1]) {
            return query(id << 1, l, mid, k);
        } else {
            return b[id << 1] + query(id << 1 | 1, mid + 1, r, k - a[id << 1]);
        }
    }
} seg;

struct BIT {
    pll a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, ll p, ll q) {
        for (; x < 110; x += x & -x) {
            a[x].fi += p;
            a[x].se += q;
        }
    }
    pll query(int x) {
        pll res = pll(0, 0);
        for (; x > 0; x -= x & -x) {
            res.fi += a[x].fi;
            res.se += a[x].se;
        }
        return res;
    }
} bit;

int main() {
    while (scanf("%d%d", &n, &M) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", t + i);
        }
        seg.init();
        for (int i = 1; i <= n; ++i) {
            ll remind = M - t[i];
            printf("%lld%c", i - 1 - seg.query(1, 1, 100, remind), " \n"[i == n]);
            seg.update(1, 1, 100, t[i]);
        }
    }
    return 0;
}
