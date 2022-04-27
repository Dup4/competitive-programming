#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using pLI = pair<ll, int>;
#define fi first
#define se second
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
const int N = 3e5 + 10;
const ll INF = 2e18;
int n, C, a[N];
ll S[N];

namespace WQS {
// 0 前i个位置的最值
// 1 前i个位置，并且第i个位置是集结点的最值
struct frac {
    db x, y;
    frac(db x = 0, db y = 0) : x(x), y(y) {}
    bool operator<(const frac &other) const {
        return x * other.y < other.x * y;
    }
    bool operator>(const frac &other) const {
        return x * other.y > other.x * y;
    }
};
ll f[2][N];
db y[2][N], x[2][N];
int cnt[2][N];
int que[2][N], head[2], tail[2];
frac slope(int k, int j, int id) {
    return frac(y[id][j] - y[id][k], x[id][j] - x[id][k]);
}
pLI check(ll k) {
    head[0] = 1;
    tail[0] = 0;
    head[1] = 1;
    tail[1] = 0;
    que[0][++tail[0]] = 0;
    for (int i = 1, j; i <= n; ++i) {
        //第i个位置是集结点的最值
        while (head[0] < tail[0] && slope(que[0][head[0]], que[0][head[0] + 1], 0) < frac(a[i], 1)) ++head[0];
        j = que[0][head[0]];
        f[1][i] = f[0][j] - (S[i] - S[j]) + 1ll * (i - j) * a[i] + k;
        cnt[1][i] = cnt[0][j] + 1;
        y[1][i] = f[1][i] - S[i] + 1ll * i * a[i];
        x[1][i] = a[i];
        while (head[1] < tail[1] && slope(que[1][tail[1] - 1], que[1][tail[1]], 1) > slope(que[1][tail[1]], i, 1))
            --tail[1];
        que[1][++tail[1]] = i;
        //前i个位置的最值
        while (head[1] < tail[1] && slope(que[1][head[1]], que[1][head[1] + 1], 1) < frac(i, 1)) ++head[1];
        j = que[1][head[1]];
        f[0][i] = f[1][j] + (S[i] - S[j]) - 1ll * (i - j) * a[j];
        cnt[0][i] = cnt[1][j];
        y[0][i] = f[0][i] + S[i];
        x[0][i] = i;
        while (head[0] < tail[0] && slope(que[0][tail[0] - 1], que[0][tail[0]], 0) > slope(que[0][tail[0]], i, 0))
            --tail[0];
        que[0][++tail[0]] = i;
    }
    return pLI(f[0][n], cnt[0][n]);
}
void gao() {
    ll l = 0, r = S[n] + 1, pos = 0;
    while (r - l >= 0) {
        ll mid = (l + r) >> 1;
        if (check(mid).se <= C) {
            r = mid - 1;
            pos = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%lld\n", check(pos).fi - 1ll * pos * C);
}
}  // namespace WQS

int main() {
    while (scanf("%d%d", &n, &C) != EOF) {
        S[0] = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), S[i] = S[i - 1] + a[i];
        WQS::gao();
    }
    return 0;
}
