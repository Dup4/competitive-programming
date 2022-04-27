#include <bits/stdc++.h>
using namespace std;
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
void err(const T& arg, const Ts&... args) {
    cout << arg << ' ';
    err(args...);
}
#define fi first
#define se second
const int N = 1e3 + 10;
int n, m, q, g[N][N], res;

struct UFS {
    int fa[N * N];
    void init() {
        memset(fa, 0, sizeof fa);
    }
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    int join(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            fa[fx] = fy;
            return 1;
        }
        return 0;
    }
} ufs;

int Move[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

inline int id(int x, int y) {
    return (x - 1) * m + y;
}
inline bool ok(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m || g[x][y] == 0)
        return false;
    return true;
}
inline void add(int x, int y) {
    ++res;
    for (int j = 0; j < 4; ++j) {
        int nx = x + Move[j][0];
        int ny = y + Move[j][1];
        if (ok(nx, ny)) {
            res -= ufs.join(id(x, y), id(nx, ny));
        }
    }
}
inline void add1(int x, int l, int r) {
    for (int y = l; y <= r; ++y) {
        if (g[x][y] == 0) {
            g[x][y] = 1;
            add(x, y);
        }
    }
}

struct ODT {
    struct node {
        int l, r;
        mutable int v;
        node(int l, int r = -1, int v = 0) : l(l), r(r), v(v) {}
        bool operator<(const node& other) const {
            return l < other.l;
        }
    };
    using IT = set<node>::iterator;
    set<node> se;
    void init() {
        se.clear();
    }
    IT split(int pos) {
        IT it = se.lower_bound(node(pos));
        if (it != se.end() && it->l == pos)
            return it;
        --it;
        int l = it->l, r = it->r;
        int v = it->v;
        se.erase(it);
        se.insert(node(l, pos - 1, v));
        return se.insert(node(pos, r, v)).first;
    }
    void assign(int x, int l, int r) {
        IT itr = split(r + 1), itl = split(l);
        for (IT it = itl; it != itr; ++it) {
            if (it->v == 0) {
                add1(x, it->l, it->r);
            }
        }
        se.erase(itl, itr);
        se.insert(node(l, r, 1));
    }
} odt[N];

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(g, 0, sizeof g);
        res = 0;
        ufs.init();
        for (int i = 1; i <= n; ++i) odt[i].init(), odt[i].se.insert(ODT::node(1, m, 0));
        for (int i = 1; i <= n; ++i) {
            static char s[N];
            scanf("%s", s + 1);
            for (int j = 1; j <= m; ++j) {
                g[i][j] = s[j] - '0';
                if (g[i][j] == 1)
                    add(i, j);
            }
        }
        scanf("%d", &q);
        for (int i = 1, x[2], y[2]; i <= q; ++i) {
            scanf("%d%d%d%d", x, y, x + 1, y + 1);
            for (int j = x[0]; j <= x[1]; ++j) {
                odt[j].assign(j, y[0], y[1]);
            }
            printf("%d\n", res);
        }
    }
    return 0;
}
