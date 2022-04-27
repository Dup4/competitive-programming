#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
#define fi first
#define se second
#define SZ(x) (int(x.size()))
const int N = 1e5 + 10, M = 20;
const ll INFLL = 1e18;
int n, L, R, q, a[N];
// 0 L 1 R
ll S[N];

vector<vector<int>> G;

struct RMQ {
    ll Max[N][M];
    ll Min[N][M];
    int mm[N];
    void init(int n, ll *b) {
        mm[0] = -1;
        for (int i = 1; i <= n; ++i) {
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
            Max[i][0] = b[i];
            Min[i][0] = b[i];
        }
        for (int j = 1; j <= mm[n]; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
                Min[i][j] = min(Min[i][j - 1], Min[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    ll queryMax(int x, int y) {
        int k = mm[y - x + 1];
        return max(Max[x][k], Max[y - (1 << k) + 1][k]);
    }
    ll queryMin(int x, int y) {
        int k = mm[y - x + 1];
        return min(Min[x][k], Min[y - (1 << k) + 1][k]);
    }
    int queryL(int x, ll ini) {
        int l = x, r = n, res = n;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (ini + queryMin(x, mid) - S[x - 1] <= L) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return res + 1;
    }
    int queryR(int x, ll ini) {
        int l = x, r = n, res = n;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (ini + queryMax(x, mid) - S[x - 1] >= R) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return res + 1;
    }
} rmq;

void addEdge(int ini, int id) {
    int nl = rmq.queryL(id / 2, ini);
    int nr = rmq.queryR(id / 2, ini);
    if (nl < nr) {
        // dbg(nl * 2, id);
        G[nl * 2].push_back(id);
    } else {
        // dbg(nr * 2 + 1, id);
        G[nr * 2 + 1].push_back(id);
    }
}

int fa[M][N * 2 + 10];

void dfs(int u) {
    for (int i = 1; i < M; ++i) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (auto &v : G[u]) {
        fa[0][v] = u;
        dfs(v);
    }
}

ll get(int u, int E) {
    // dbg(u, E);
    for (int i = M - 1; i >= 0; --i) {
        if (fa[i][u] / 2 <= E)
            u = fa[i][u];
    }
    // dbg(u, E);
    ll ans = u % 2 ? R : L;
    ans += S[E] - S[u / 2 - 1];
    if (ans > R)
        ans = R;
    if (ans < L)
        ans = L;
    return ans;
}

int main() {
    scanf("%d%d%d", &n, &L, &R);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i), S[i] = S[i - 1] + a[i];
    rmq.init(n, S);
    G.clear();
    G.resize(n * 2 + 20);
    for (int i = 1; i <= n; ++i) {
        addEdge(L, 2 * i);
        addEdge(R, 2 * i + 1);
    }
    fa[0][2 * (n + 1)] = 2 * (n + 1);
    fa[0][2 * (n + 1) + 1] = 2 * (n + 1) + 1;
    dfs(2 * (n + 1));
    dfs(2 * (n + 1) + 1);
    scanf("%d", &q);
    for (int i = 1, B, E, X; i <= q; ++i) {
        scanf("%d%d%d", &B, &E, &X);
        int nl = rmq.queryL(B, X);
        int nr = rmq.queryR(B, X);
        if (min(nl, nr) - 1 >= E) {
            ll ans = S[E] - S[B - 1] + X;
            if (ans > R)
                ans = R;
            if (ans < L)
                ans = L;
            printf("%lld\n", ans);
        } else {
            int id;
            if (nl < nr)
                id = nl * 2;
            else
                id = nr * 2 + 1;
            printf("%lld\n", get(id, E));
        }
    }
    return 0;
}
