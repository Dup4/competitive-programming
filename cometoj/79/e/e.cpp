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
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
#define fi first
#define se second
const int N = 2e5 + 10, INF = 0x3f3f3f3f;
int n, q, val[N], ans[N];
vector<vector<pII>> op, query;

struct SEG {
    struct node {
        int Max, lazy;
        node() {
            Max = 0;
            lazy = 0;
        }
        void up(int x) {
            Max += x;
            lazy += x;
        }
        node operator+(const node &other) const {
            node res = node();
            res.Max = max(Max, other.Max);
            return res;
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void down(int id) {
        int &lazy = t[id].lazy;
        if (!lazy)
            return;
        t[id << 1].up(lazy);
        t[id << 1 | 1].up(lazy);
        lazy = 0;
    }
    void update(int id, int l, int r, int ql, int qr, int v) {
        if (ql > qr)
            return;
        if (l >= ql && r <= qr) {
            t[id].up(v);
            return;
        }
        int mid = (l + r) >> 1;
        down(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    int query(int id, int l, int r, int x) {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        down(id);
        if (t[id << 1 | 1].Max >= x)
            return query(id << 1 | 1, mid + 1, r, x);
        else
            return query(id << 1, l, mid, x);
    }
    int query1(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr)
            return t[id].Max;
        int mid = (l + r) >> 1;
        down(id);
        int res = -INF;
        if (ql <= mid)
            res = max(res, query1(id << 1, l, mid, ql, qr));
        if (qr > mid)
            res = max(res, query1(id << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
} seg;

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        op.clear();
        op.resize(n + 5);
        query.clear();
        query.resize(n + 5);
        seg.build(1, 1, q);
        for (int i = 1; i <= q; ++i) {
            static char sop[10];
            static int x, y;
            scanf("%s%d%d", sop, &x, &y);
            if (strcmp(sop, "push") == 0) {
                scanf("%d", val + i);
                op[x].push_back(pII(i, 1));
                op[y + 1].push_back(pII(i, -1));
            } else if (strcmp(sop, "pop") == 0) {
                op[x].push_back(pII(i, -1));
                op[y + 1].push_back(pII(i, 1));
            } else {
                query[x].push_back(pII(y, i));
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (auto &it : op[i]) {
                seg.update(1, 1, q, 1, it.fi, it.se);
            }
            for (auto &it : query[i]) {
                int t = seg.query1(1, 1, q, it.se + 1, it.se + 1);
                // dbg(i, it.fi, it.se, t, seg.query1(1, 1, q, it.se, it.se), seg.query1(1, 1, q, 5, 5));
                seg.update(1, 1, q, it.se + 1, q, -INF);
                ans[it.se] = seg.query(1, 1, q, it.fi + t);
                seg.update(1, 1, q, it.se + 1, q, INF);
            }
        }
        for (int i = 1; i <= q; ++i)
            if (ans[i])
                printf("%d\n", val[ans[i]]);
    }
    return 0;
}
