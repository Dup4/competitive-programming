#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
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
int n, m, q, a[N], used[N], b[N], c[N];

namespace IO {
const int S = (1 << 20) + 5;
char buf[S], *H, *T;
inline char Get() {
    if (H == T)
        T = (H = buf) + fread(buf, 1, S, stdin);
    if (H == T)
        return -1;
    return *H++;
}
inline int read() {
    int x = 0, fg = 1;
    char c = Get();
    while (!isdigit(c) && c != '-') c = Get();
    if (c == '-')
        fg = -1, c = Get();
    while (isdigit(c)) x = x * 10 + c - '0', c = Get();
    return x * fg;
}
};  // namespace IO
using namespace IO;

struct Hash {
    constexpr static ll seed[2] = {233, 13331};
    constexpr static ll mod[2] = {998244353, 1000000007};
    static ll base[2][N];
    static void init() {
        base[0][0] = base[1][0] = 1;
        for (int i = 1; i < N; ++i) {
            // base[0][i] = base[0][i - 1] * seed[0] % mod[0];
            base[1][i] = base[1][i - 1] * seed[1] % mod[1];
        }
    }
    ll a[2][N];
    void clear() {
        a[1][0] = 0;
    }
    void add(int x, int y) {
        // a[0][x] = (a[0][x - 1] * seed[0] % mod[0] + y + 1) % mod[0];
        a[1][x] = (a[1][x - 1] * seed[1] % mod[1] + y + 1) % mod[1];
    }
    ll get(int x) {
        return a[1][x];
    }
} hs;
ll Hash::base[2][N] = {{0}, {0}};
gp_hash_table<ll, int> mp[N];

inline bool gao() {
    hs.clear();
    c[0] = read();
    for (int i = 1; i <= *c; ++i) {
        c[i] = read();
        hs.add(i, c[i]);
    }
    return mp[*c][hs.get(*c)];
}

int main() {
    Hash::init();
    int _T;
    _T = read();
    while (_T--) {
        n = read();
        q = read();
        for (int i = 1; i <= n; ++i) mp[i].clear();
        for (int i = 1; i <= n; ++i) a[i] = read();
        m = 0;
        memset(used, 0, sizeof(used[0]) * (n + 5));
        for (int i = 1; i <= n; ++i) {
            int x = a[i];
            //	dbg(i, x, used[x]);
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
                mp[k][hs.get(k)] = 1;
            }
            for (int j = m + 1; j <= n; ++j) {
                ++k;
                hs.add(k, 0);
                mp[k][hs.get(k)] = 1;
            }
        }
        //	reverse(b + 1, b + 1 + m);
        //	for (int i = 1; i <= m; ++i)
        //		printf("%d%c", b[i], " \n"[i == m]);
        while (q--) puts(gao() ? "Yes" : "No");
    }
    return 0;
}
