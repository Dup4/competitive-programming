#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
#define pli pair<ll, int>
#define pii pair<int, int>
#define fi first
#define se second
int n, m, q;
int a[N], ans[N];
pli b[N];

struct SEG {
    int a[N << 2];
    void build(int id, int l, int r) {
        a[id] = 0;
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int x) {
        if (l == r) {
            a[id] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(id << 1, l, mid, x);
        else
            update(id << 1 | 1, mid + 1, r, x);
        a[id] = a[id << 1] + a[id << 1 | 1];
    }
    int query(int id, int l, int r, int k) {
        if (l == r) {
            return l;
        }
        int mid = (l + r) >> 1;
        if (k <= a[id << 1]) {
            return query(id << 1, l, mid, k);
        } else {
            return query(id << 1 | 1, mid + 1, r, k - a[id << 1]);
        }
    }
} seg;

int main() {
    while (scanf("%d%d%d", &n, &m, &q) != EOF) {
        memset(a, 0, sizeof a);
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            ++a[x];
        }
        for (int i = 1; i <= q; ++i) {
            ll y;
            scanf("%lld", &y);
            b[i] = pli(y, i);
        }
        seg.build(1, 1, m);
        sort(b + 1, b + 1 + q);
        int pos = 1;
        ll last = n;
        int pre = 0;
        vector<pii> vec;
        for (int i = 1; i <= m; ++i) {
            if (!a[i]) {
                seg.update(1, 1, m, i);
            } else {
                vec.push_back(pii(a[i], i));
            }
        }
        sort(vec.begin(), vec.end());
        for (auto it : vec) {
            int tot = seg.a[1];
            ll nx = last + 1ll * tot * (it.fi - pre);
            //  cout << nx << endl;
            for (; pos <= q && b[pos].fi <= nx; ++pos) {
                ll need = b[pos].fi - last;
                ans[b[pos].se] = seg.query(1, 1, m, (need - 1) % tot + 1);
            }
            seg.update(1, 1, m, it.se);
            last = nx;
            pre = it.fi;
        }
        for (; pos <= q; ++pos) {
            ll need = b[pos].fi - last;
            ans[b[pos].se] = seg.query(1, 1, m, (need - 1) % m + 1);
        }
        for (int i = 1; i <= q; ++i) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
