#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 10;

struct Edge {
    int to, nxt;
    Edge() {}
    Edge(int to, int nxt) : to(to), nxt(nxt) {}
} edge[maxn << 1];

int n;
int arr[maxn];
int head[maxn], tot;
int vis[maxn];
int fa[maxn];
int sze[maxn];
int cnt[maxn];
int cnt2[maxn];
int du[maxn];

void Init() {
    tot = 0;
    memset(head, -1, sizeof head);
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
        sze[i] = 1;
        cnt[i] = 0;
        cnt2[i] = 0;
        vis[i] = 0;
        du[i] = 0;
    }
}

void addedge(int u, int v) {
    edge[tot] = Edge(v, head[u]);
    head[u] = tot++;
    edge[tot] = Edge(u, head[v]);
    head[v] = tot++;
}

int find(int x) {
    return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);
}

void Unin(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (sze[x] < sze[y]) {
            sze[x] = sze[y] + 1;
            fa[y] = x;
        } else {
            sze[y] = sze[x] + 1;
            fa[x] = y;
        }
    }
}

void solve() {
    int ans = 0;
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (du[i] == 1) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].to;
            if (!vis[u] && !vis[v]) {
                vis[u] = vis[v] = 1;
            }
            --du[v];
            if (du[v] == 1) {
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i] && !vis[arr[i]]) {
            Unin(i, arr[i]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            cnt[find(i)]++;
        }
    }
    for (int i = 1; i <= n; ++i) {
        ans += (cnt[i]) % 2;
    }
    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d", &n)) {
        Init();
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            addedge(i, x);
            du[i]++;
            du[x]++;
            arr[i] = x;
        }
        solve();
    }
    return 0;
}
