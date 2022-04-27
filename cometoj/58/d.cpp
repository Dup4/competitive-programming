#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
const int N = 1e6 + 10;
int n, m, q, a[N];
int pl[N], pr[N];
vector<vector<int>> add;
vector<vector<pii>> qvec;

struct BIT {
    ll a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void add(int x, ll v) {
        for (; x < N; x += x & -x) {
            a[x] += v;
        }
    }
    ll query(int x) {
        ll res = 0;
        for (; x > 0; x -= x & -x) res += a[x];
        return res;
    }
    void update(int l, int r, ll v) {
        add(l, v);
        add(r + 1, -v);
    }
} bit;

void Max(int &x, int y) {
    if (x < y)
        x = y;
}
void Min(int &x, int y) {
    if (x > y)
        x = y;
}

int main() {
    while (scanf("%d%d%d", &n, &m, &q) != EOF) {
        add.clear();
        add.resize(n + 1);
        qvec.clear();
        qvec.resize(n + 1);
        bit.init();
        for (int i = 1; i <= n; ++i) {
            pl[i] = 0, pr[i] = n + 1;
        }
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            if (v < u)
                Max(pl[u], v);
            else
                Min(pr[u], v);
        }
        //	for (int i = 1; i <= n; ++i) printf("%d %d %d\n", i, pl[i], pr[i]);
        for (int i = 1; i <= n; ++i) {
            add[pl[i] + 1].push_back(i);
        }
        for (int i = 1, l, r; i <= q; ++i) {
            scanf("%d%d", &l, &r);
            qvec[l].push_back(pii(r, i));
        }
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            for (auto it : add[i]) {
                //	cout << i << " " << it << " " << pr[it] - 1 << endl;
                bit.update(it, pr[it] - 1, a[it]);
            }
            for (auto it : qvec[i]) {
                //		cout << i << " " << it.fi << " " << bit.query(it.fi) << endl;
                res ^= 1ll * it.se * bit.query(it.fi);
            }
            bit.update(i, pr[i] - 1, -a[i]);
        }
        printf("%lld\n", res);
    }
    return 0;
}
