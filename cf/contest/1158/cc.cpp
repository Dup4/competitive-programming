#include <bits/stdc++.h>
using namespace std;

#define N 500010
int n, a[N];
struct SEG {
    struct node {
        int x, lazy;
        node() {}
        node(int x, int lazy) : x(x), lazy(lazy) {}
        void add(int v) {
            x = v;
            lazy = v;
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id] = node(0, 0);
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void pushdown(int id) {
        int &x = t[id].lazy;
        if (x) {
            t[id << 1].add(x);
            t[id << 1 | 1].add(x);
            x = 0;
        }
    }
    void update(int id, int l, int r, int ql, int qr, int v) {
        if (l > r) {
            return;
        }
        if (l >= ql && r <= qr) {
            t[id].add(v);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
    }
    int query(int id, int l, int r, int pos) {
        if (l == r) {
            return t[id].x;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (pos <= mid)
            return query(id << 1, l, mid, pos);
        else
            return query(id << 1 | 1, mid + 1, r, pos);
    }
} seg;
int d[N];
vector<vector<int> > G;
int res[N], ord[N];

void Toposort() {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (d[i] == 0) {
            q.push(i);
        }
    }
    int m = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord[++m] = u;
        for (auto v : G[u]) {
            if (--d[v] == 0) {
                q.push(v);
            }
        }
    }
    if (m < n) {
        puts("-1");
    } else {
        for (int i = 1; i <= n; ++i) {
            res[ord[i]] = i;
        }
        for (int i = 1; i <= n; ++i) {
            printf("%d%c", res[i], " \n"[i == n]);
        }
    }
}

void init() {
    G.clear();
    G.resize(n + 2);
    for (int i = 1; i <= n; ++i) {
        d[i] = 0;
    }
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        init();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        for (int i = 1; i <= n; ++i) {
            if (a[i] != -1) {
                G[i].push_back(a[i]);
                ++d[a[i]];
                for (int j = i + 1; j < a[i]; ++j) {
                    G[j].push_back(i);
                    ++d[i];
                }
            }
        }
        Toposort();
    }
    return 0;
}
