#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
int n, m, q;
inline int sum(ll x) {
    int res = 0;
    while (x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}
struct node {
    int y, f;
    node() {}
    node(int y, int f) : y(y), f(f) {}
};
struct qnode {
    int l, r, f, id;
    qnode() {}
    qnode(int l, int r, int f, int id) : l(l), r(r), f(f), id(id) {}
};
vector<vector<node>> add;
vector<vector<qnode>> qvec;
ll ans[N];

struct BIT {
    ll a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    inline void update(int x, int v) {
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
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &q);
        bit.init();
        add.clear();
        add.resize(n + 1);
        qvec.clear();
        qvec.resize(n + 1);
        for (int i = 1, x, y; i <= m; ++i) {
            scanf("%d%d", &x, &y);
            ll a, b, c, d, f = 0;
            a = x - (n / 2 + 1);
            b = y - (n / 2 + 1);
            d = max(abs(a), abs(b));
            c = (n / 2) - d;
            f = 2ll * c * (n - 1 + n - (c * 2) + 1);
            if (a == 0 && b == 0)
                ++f;
            else if (a == d) {
                f += n - c - y + 1;
            } else if (b == d * (-1)) {
                f += (n - c * 2 - 1) + (n - c - x + 1);
            } else if (a == d * (-1)) {
                f += (n - c * 2 - 1) * 2 + (y - c);
            } else if (b == d) {
                f += (n - c * 2 - 1) * 3 + (x - c);
            }
            add[x].push_back(node(y, sum(f)));
        }
        //	for (int i = 1; i <= m; ++i)
        //		printf("%d %d %lld\n",x[i],y[i],f[i]);
        for (int i = 1, x1, y1, x2, y2; i <= q; ++i) {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            qvec[x1 - 1].push_back(qnode(y1, y2, -1, i));
            qvec[x2].push_back(qnode(y1, y2, 1, i));
            ans[i] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            for (auto &it : add[i]) bit.update(it.y, it.f);
            for (auto &it : qvec[i]) ans[it.id] += bit.query(it.l, it.r) * it.f;
        }
        for (int i = 1; i <= q; ++i) printf("%lld\n", ans[i]);
    }
    return 0;
}
