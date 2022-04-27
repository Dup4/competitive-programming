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
    int fa[N * N], sze[N * N];
    void init() {
        for (int i = 1; i <= n * m; ++i) {
            fa[i] = 0;
            sze[i] = 1;
        }
    }
    int find(int x) {
        return fa[x] == 0 ? x : fa[x] = find(fa[x]);
    }
    int join(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            if (sze[fx] > sze[fy])
                swap(fx, fy);
            fa[fx] = fy;
            if (sze[fy] == sze[fx])
                ++sze[fy];
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

struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) a[x] += v;
    }
    int query(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) res += a[x];
        return res;
    }
    int query(int l, int r) {
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
} bit[N];

struct SEG {
    struct node {
        int Min, pos;
        node() {
            Min = 0, pos = -1;
        }
        node(int Min, int pos) : Min(Min), pos(pos) {}
        node operator+(const node& other) const {
            node res = node();
            if (Min < other.Min) {
                res.Min = Min;
                res.pos = pos;
            } else {
                res.Min = other.Min;
                res.pos = other.pos;
            }
            return res;
        }
    } t[N << 2], res;
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            t[id].pos = l;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update(int id, int l, int r, int pos) {
        if (l == r) {
            t[id].Min = 1;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos);
        else
            update(id << 1 | 1, mid + 1, r, pos);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            res = res + t[id];
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            query(id << 1 | 1, mid + 1, r, ql, qr);
    }
} seg[N];

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(g, 0, sizeof g);
        res = 0;
        ufs.init();
        for (int i = 1; i <= n; ++i) {
            seg[i].build(1, 1, m);
            bit[i].init();
        }
        for (int i = 1; i <= n; ++i) {
            static char s[N];
            scanf("%s", s + 1);
            for (int j = 1; j <= m; ++j) {
                g[i][j] = s[j] - '0';
                if (g[i][j] == 1) {
                    add(i, j);
                    seg[i].update(1, 1, m, j);
                    bit[i].update(j, 1);
                }
            }
        }
        scanf("%d", &q);
        for (int i = 1, x[2], y[2]; i <= q; ++i) {
            scanf("%d%d%d%d", x, y, x + 1, y + 1);
            for (int j = x[0]; j <= x[1]; ++j) {
                while (1) {
                    if (bit[j].query(y[0], y[1]) == y[1] - y[0] + 1)
                        break;
                    seg[j].res = SEG::node(1, y[0]);
                    seg[j].query(1, 1, m, y[0], y[1]);
                    int pos = seg[j].res.pos;
                    for (int k = pos; k <= y[1]; ++k) {
                        if (g[j][k] == 0) {
                            g[j][k] = 1;
                            seg[j].update(1, 1, m, k);
                            add(j, k);
                            bit[j].update(k, 1);
                        } else {
                            break;
                        }
                    }
                }
            }
            printf("%d\n", res);
        }
    }
    return 0;
}
