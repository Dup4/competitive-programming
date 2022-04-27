#include <bits/stdc++.h>
using namespace std;
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
    cout << arg << ' ';
    err(args...);
}
constexpr int N = 2e5 + 10, M = 5e5 + 10;
int n, m, A, B;
struct Edge {
    int v, nx, cut;
} e[M << 1];
int h[N], tot;
inline void addedge(int u, int v) {
    e[tot] = {v, h[u], 0};
    h[u] = tot++;
}

struct UFS {
    int fa[N], sze[N];
    void init() {
        for (int i = 1; i <= n; ++i) {
            fa[i] = 0;
            sze[i] = 1;
        }
    }
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    void merge(int u, int v) {
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            if (sze[fu] > sze[fv])
                swap(fu, fv);
            fa[fu] = fv;
            sze[fv] += sze[fu];
        }
    }
} ufs;

int gao(int A, int B) {
    ufs.init();
    for (int u = 1; u <= n; ++u) {
        for (int i = h[u]; ~i; i = e[i].nx) {
            int v = e[i].v;
            if (u != A && v != A) {
                ufs.merge(u, v);
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        if (i != A && ufs.find(i) != ufs.find(B))
            ++res;
    }
    return res;
}

void run() {
    scanf("%d%d%d%d", &n, &m, &A, &B);
    tot = 0;
    for (int i = 1; i <= n; ++i) h[i] = -1;
    for (int i = 1, u, v; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    int numA = gao(A, B), numB = gao(B, A);
    printf("%lld\n", 1ll * numA * numB);
}

int main() {
    int _T;
    cin >> _T;
    while (_T--) run();
    return 0;
}
