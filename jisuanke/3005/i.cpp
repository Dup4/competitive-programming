#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 2e5 + 10;
int n, q, a[N], b[N], ans[N];
vector<vector<int>> add;
vector<vector<pII>> qvec;
struct BIT {
    ll a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) a[x] += v;
    }
    ll query(int x) {
        ll res = 0;
        for (; x > 0; x -= x & -x) res += a[x];
        return res;
    }
    void update(int l, int r, int v) {
        update(l, v);
        update(r + 1, -v);
    }
} bit;

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        add.clear();
        add.resize(n + 1);
        qvec.clear();
        qvec.resize(n + 1);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), b[a[i]] = i;
        for (int i = 1; i <= n; ++i) {
            for (int j = i * 2; j <= n; j += i) {
                int l = b[i], r = b[j];
                if (l > r)
                    swap(l, r);
                add[r].push_back(l);
            }
        }
        for (int i = 1, l, r; i <= q; ++i) {
            scanf("%d%d", &l, &r);
            qvec[r].push_back(pII(l, i));
        }
        memset(ans, 0, sizeof ans);
        bit.init();
        for (int i = 1; i <= n; ++i) {
            for (auto &it : add[i]) {
                bit.update(1, it, 1);
            }
            for (auto &it : qvec[i]) {
                ans[it.se] = bit.query(it.fi);
            }
        }
        for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
    }
    return 0;
}
