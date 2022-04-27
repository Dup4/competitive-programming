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
} e[M];
int h[N], tot;
inline void addedge(int u, int v) {
    e[tot] = {v, h[u], 0};
    h[u] = tot++;
}
struct Tarjan {
    int Low[N], DFN[N], add_block[N], cut[N], bridge;
    bool Insta[N];
    void dfs(int u, int pre) {
        Low[u] = DFN[u] = ++*Low;
        Insta[u] = 1;
        int son = 0;
        int pre_cnt = 0;
        for (int i = h[u]; ~i; i = e[i].nx) {
            int v = e[i].v;
            //处理重边
            if (v == pre && pre_cnt == 0) {
                pre_cnt++;
                continue;
            }
            if (!DFN[v]) {
                ++son;
                dfs(v, u);
                Low[u] = min(Low[u], Low[v]);
                if (Low[v] > DFN[u]) {
                    ++bridge;
                    e[i].cut = 1;
                    e[i ^ 1].cut = 1;
                }
                if (u != pre && Low[v] >= DFN[u]) {
                    cut[u] = 1;
                    ++add_block[u];
                }
            } else
                Low[u] = min(Low[u], DFN[v]);
        }
        if (u == pre && son > 1)
            cut[u] = 1;
        if (u == pre)
            add_block[u] = son - 1;
        Insta[u] = 0;
    }
    void gao(int n) {
        memset(DFN, 0, sizeof(DFN[0]) * (n + 10));
        memset(Insta, 0, sizeof(Insta[0]) * (n + 10));
        memset(cut, 0, sizeof(cut[0]) * (n + 10));
        *Low = 0;
        for (int i = 1; i <= n; ++i)
            if (!DFN[i])
                dfs(i, i);
    }
} tarjan;

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

void run() {
    scanf("%d%d%d%d", &n, &m, &A, &B);
    ufs.init();
    tot = 0;
    for (int i = 1; i <= n; ++i) h[i] = -1;
    for (int i = 1, u, v; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    tarjan.gao(n);
    if (tarjan.cut[A] == 0 || tarjan.cut[B] == 0) {
        puts("0");
        return;
    }
    for (int u = 1; u <= n; ++u) {
        for (int i = h[u]; ~i; i = e[i].nx) {
            if (e[i].cut)
                continue;
            int v = e[i].v;
            ufs.merge(u, v);
        }
    }
    ll numA = 0, numB = 0;
    for (int i = h[A]; ~i; i = e[i].nx) {
        int v = e[i].v;
        if (ufs.find(v) == ufs.find(B))
            continue;
        numA += ufs.sze[ufs.find(v)];
    }
    for (int i = h[B]; ~i; i = e[i].nx) {
        int v = e[i].v;
        if (ufs.find(v) == ufs.find(A))
            continue;
        dbg(v);
        numB += ufs.sze[ufs.find(v)];
    }
    printf("%lld\n", 1ll * numA * numB);
}

int main() {
    int _T;
    cin >> _T;
    while (_T--) run();
    return 0;
}
