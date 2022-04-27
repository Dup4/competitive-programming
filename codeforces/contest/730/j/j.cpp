#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
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
void err(const T& arg, const Ts&... args) {
    cout << arg << ' ';
    err(args...);
}

const int N = 110;
int n, f[N][N * N];
pII a[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i].fi);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i].se);
    sort(a + 1, a + 1 + n, [&](pII x, pII y) {
        return x.se > y.se;
    });
    int all = 0, vol = 0, K = -1;
    for (int i = 1; i <= n; ++i) {
        all += a[i].fi;
    }
    for (int i = 1; i <= n; ++i) {
        vol += a[i].se;
        if (K == -1 && vol >= all) {
            K = i;
        }
    }
    memset(f, -0x3f, sizeof f);
    f[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = K; j >= 1; --j) {
            for (int k = vol - a[i].se; k >= 0; --k) {
                //	dbg(i, j, k);
                f[j][k + a[i].se] = max(f[j][k + a[i].se], f[j - 1][k] + a[i].fi);
            }
        }
    }
    int Max = 0;
    for (int i = all; i <= vol; ++i) {
        Max = max(Max, f[K][i]);
    }
    printf("%d %d\n", K, all - Max);
    return 0;
}
