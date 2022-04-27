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
vector<vector<pII>> vec;

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
    int queryMax(int x, int y) {
        int k = mm[y - x + 1];
        return max(Max[x][k], Max[y - (1 << k) + 1][k]);
    }
    int queryMin(int x, int y) {
        int k = mm[y - x + 1];
        return min(Min[x][k], Min[y - (1 << k) + 1][k]);
    }
    int queryL(int x, ll ini) {
        int l = x, r = n, res = n + 1;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (ini + queryMin(x, mid) - S[x - 1] <= L) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return res;
    }
    int queryR(int x, ll ini) {
        int l = x, r = n, res = n + 1;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (ini + queryMax(x, mid) - S[x - 1] >= R) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return res;
    }
} rmq;

int cntGAO = 0;
void gao(pII it) {
    vector<pII> tmp;
    while (it.se <= n) {
        ++cntGAO;
        id[it.fi == R][it.se] = pII(SZ(vec), SZ(tmp) - 1);
        tmp.push_back(it);
        int nl = rmq.queryL(it.se, it.fi);
        int nr = rmq.queryR(it.se, it.fi);
        if (min(nl, nr) > n)
            break;
        if (nl < nr) {
            it = pII(L, nl + 1);
        } else {
            it = pII(R, nr + 1);
        }
    }
    vec.push_back(tmp);
}

int main() {
    scanf("%d%d%d", &n, &L, &R);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i), S[i] = S[i - 1] + a[i];
    rmq.init(n, S);
    vec.clear();
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 2; ++j) id[j][i] = pII(-1, -1);
    memset(id, -1, sizeof id);
    for (int i = 1; i <= n; ++i) {
        if (id[0][i] == pII(-1, -1)) {
            gao(pII(L, i));
        }
        if (id[1][i] == pII(-1, -1)) {
            gao(pII(R, i));
        }
    }
    for (auto &_vec : vec) {
        cout << "---start---\n";
        for (auto &it : _vec) cout << it.fi << " " << it.se << endl;
        cout << "---end---\n";
    }
    scanf("%d", &q);
    for (int i = 1, B, E, X; i <= q; ++i) {
        scanf("%d%d%d", &B, &E, &X);
        int nl = rmq.queryL(B, X);
        int nr = rmq.queryR(B, X);
        if (min(nl, nr) > E) {
            printf("%lld\n", S[E] - S[B - 1] + X);
        } else {
            pII it;
            if (nl < nr) {
                it = pII(0, nl + 1);
            } else {
                it = pII(1, nr + 1);
            }
            //	dbg(i, it.fi, it.se);
            pII ID = id[it.fi][it.se];
            int l = ID.se, r = SZ(vec[ID.fi]) - 1, res = r;
            while (r - l >= 0) {
                int mid = (l + r) >> 1;
                if (vec[ID.fi][mid].se <= E) {
                    res = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            ll ans = vec[ID.fi][res].fi;
            ans = ans + S[E] - S[vec[ID.fi][res].se - 1];
            if (ans > R)
                ans = R;
            if (ans < L)
                ans = L;
            printf("%lld\n", ans);
        }
    }
    return 0;
}
