#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
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
    cout << arg << " ";
    err(args...);
}
const int N = 5e3 + 10;
int n, m, q, a[N], used[N], b[N], len[N], ans[N];
ull f[N], g[N], seed = 13331;
struct Hash {
    constexpr static ull seed = 13331;
    ull a[N];
    void clear() {
        a[0] = 0;
    }
    void add(int x, int y) {
        a[x] = a[x - 1] * seed + y;
    }
    ull get(int x) {
        return a[x];
    }
} hs;

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), used[i] = 0;
        for (int i = 1; i <= q; ++i) {
            scanf("%d", len + i);
            hs.clear();
            for (int j = 1; j <= len[i]; ++j) scanf("%d", b + j), hs.add(j, b[j]);
            g[i] = hs.get(len[i]);
            ans[i] = 0;
            if (!g[i])
                ans[i] = 1;
        }
        m = 0;
        for (int i = 1; i <= n; ++i) b[i] = 0;
        for (int i = 1; i <= n; ++i) {
            int x = a[i];
            if (used[x] == 0) {
                b[++m] = x;
                used[x] = m;
            } else {
                for (int j = used[x]; j <= m; ++j) {
                    b[j] = b[j + 1];
                    used[b[j]] = j;
                }
                b[m] = x;
                used[x] = m;
            }
            hs.clear();
            int k = 0;
            for (int j = m; j >= 1; --j) {
                ++k;
                hs.add(k, b[j]);
                f[k] = hs.get(k);
            }
            for (int j = m + 1; j <= n; ++j) {
                ++k;
                hs.add(k, 0);
                f[k] = hs.get(k);
            }
            for (int j = 1; j <= q; ++j) {
                if (f[len[j]] == g[j])
                    ans[j] = 1;
            }
        }
        for (int i = 1; i <= q; ++i) puts(ans[i] ? "Yes" : "No");
    }
    return 0;
}
