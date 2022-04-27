#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define SZ(x) (int(x.size()))
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
const int N = 2e3 + 10, INF = 1e9;
int n, m, d, sx, sy, ex, ey, a[N];
pII b[N];
char G[N][N];

int Move[][2] = {1, 0, -1, 0, 0, 1, 0, -1};

struct BFS {
    int dis[N][N];
    pII pre[N][N];
    bool ok(int x, int y) {
        if (x < 1 || x > n || y < 1 || y > m || G[x][y] == 'X')
            return 0;
        return 1;
    }
    void gao(int sx, int sy) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                dis[i][j] = INF;
                pre[i][j] = pII(-1, -1);
            }
        }
        dis[sx][sy] = 0;
        queue<pII> que;
        que.push(pII(sx, sy));
        while (!que.empty()) {
            int x = que.front().fi, y = que.front().se;
            que.pop();
            for (int i = 0; i < 4; ++i) {
                int nx = x + Move[i][0];
                int ny = y + Move[i][1];
                if (ok(nx, ny) && dis[nx][ny] > dis[x][y] + 1) {
                    dis[nx][ny] = dis[x][y] + 1;
                    pre[nx][ny] = pII(x, y);
                    que.push(pII(nx, ny));
                }
            }
        }
    }
} f, g;

struct DEQUE {
    int que[N], head, tail;
    void init() {
        head = 1, tail = 0;
    }
} q[N];

struct SEG {
    struct node {
        int Min;
        pII pos;
        node() {
            Min = INF;
            pos = pII(-1, -1);
        }
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
            t[id].Min = a[l];
            t[id].pos = b[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    //	void update(int id, int l, int r, int pos, int v) {
    //		if (l == r) {
    //			t[id].Min = v;
    //			return;
    //		}
    //		int mid = (l + r) >> 1;
    //		if (pos <= mid) update(id << 1, l, mid, ql, qr, v);
    //		else update(id << 1 | 1, mid + 1, r, ql, qr, v);
    //		t[id] = t[id << 1] + t[id << 1 | 1];
    //	}
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
} seg;

int main() {
    scanf("%d%d%d", &n, &m, &d);
    for (int i = 1; i <= n; ++i) scanf("%s", G[i] + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (G[i][j] == 'S') {
                sx = i, sy = j;
            } else if (G[i][j] == 'T') {
                ex = i, ey = j;
            }
        }
    }
    //	dbg(sx, sy, ex, ey);
    f.gao(sx, sy);
    g.gao(ex, ey);
    //	for (int i = 1; i <= n; ++i) {
    //		for (int j = 1; j <= m; ++j) {
    //			dbg(i, j, f.dis[i][j]);
    //		}
    //	}

    //	for (int i = 1; i <= n; ++i) {
    //		for (int j = 1; j <= m; ++j) {
    //			dbg(i, j, g.dis[i][j]);
    //		}
    //	}
    for (int i = 1; i <= m; ++i) q[i].init();
    int up = 1, down = 0;
    pII A = pII(ex, ey), B = pII(-1, -1);
    int dis = f.dis[ex][ey];
    for (int i = 1; i <= n; ++i) {
        up = max(1, i - d);
        int _down = min(n, i + d);
        while (down < _down) {
            ++down;
            for (int j = 1; j <= m; ++j) {
                while (q[j].head <= q[j].tail && g.dis[q[j].que[q[j].tail]][j] >= g.dis[down][j]) --q[j].tail;
                q[j].que[++q[j].tail] = down;
            }
        }
        for (int j = 1; j <= m; ++j) {
            while (q[j].head <= q[j].tail && q[j].que[q[j].head] < up) ++q[j].head;
            a[j] = g.dis[q[j].que[q[j].head]][j];
            b[j] = pII(q[j].que[q[j].head], j);
        }
        seg.build(1, 1, m);
        for (int j = 1; j <= m; ++j)
            if (G[i][j] != 'X') {
                int l = max(1, j - d);
                int r = min(m, j + d);
                seg.res = SEG::node();
                seg.query(1, 1, m, l, r);
                pII _A = pII(i, j);
                pII _B = seg.res.pos;
                int _dis = f.dis[i][j] + seg.res.Min + 1;
                if (_dis <= dis) {
                    //	dbg(i, j, f.dis[i][j], g.dis[_B.fi][_B.se], _B.fi, _B.se);
                    dis = _dis;
                    A = _A;
                    B = _B;
                }
            }
    }
    if (dis >= INF)
        puts("-1");
    else {
        printf("%d\n", dis);
        vector<pII> vecA, vecB;
        while (A != pII(-1, -1)) {
            vecA.push_back(A);
            A = f.pre[A.fi][A.se];
        }
        while (B != pII(-1, -1)) {
            vecB.push_back(B);
            B = g.pre[B.fi][B.se];
        }
        reverse(vecA.begin(), vecA.end());
        for (int i = 0; i < SZ(vecA); ++i) {
            printf("%d %d\n", vecA[i].fi - 1, vecA[i].se - 1);
        }
        for (int i = 0; i < SZ(vecB); ++i) {
            printf("%d %d\n", vecB[i].fi - 1, vecB[i].se - 1);
        }
    }
    return 0;
}
