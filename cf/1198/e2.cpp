#include <bits/stdc++.h>
using namespace std;
 
#define INF 0x3f3f3f3f
#define N 1010
#define M 100010
 
struct Edge {
    int to, flow, nxt;
 
    Edge() {}
 
    Edge(int to, int nxt, int flow) : to(to), nxt(nxt), flow(flow) {}
} edge[M << 1];
 
struct node {
    int x[2], y[2];
 
    void input() {
        scanf("%d %d %d %d", x, y, x + 1, y + 1);
        --x[0], --y[0];
    }
} a[N];
 
int head[N], tot;
int dep[N];
int S, T, n, m;
int X[N], Y[N];
 
void Init() {
    memset(head, -1, sizeof head);
    tot = 0;
}
 
void addedge(int u, int v, int w, int rw = 0) {
    edge[tot] = Edge(v, head[u], w);
    head[u] = tot++;
    edge[tot] = Edge(u, head[v], rw);
    head[v] = tot++;
}
 
bool BFS() {
    memset(dep, -1, sizeof dep);
    queue<int> q;
    q.push(S);
    dep[S] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            if (edge[i].flow && dep[edge[i].to] == -1) {
                dep[edge[i].to] = dep[u] + 1;
                q.push(edge[i].to);
            }
        }
    }
    return dep[T] >= 0;
}
 
int DFS(int u, int f) {
    if (u == T || f == 0) {
        return f;
    }
    int w, used = 0;
    for (int i = head[u]; ~i; i = edge[i].nxt) {
        if (edge[i].flow && dep[edge[i].to] == dep[u] + 1) {
            w = DFS(edge[i].to, min(f - used, edge[i].flow));
            edge[i].flow -= w;
            edge[i ^ 1].flow += w;
            used += w;
            if (used == f) {
                return f;
            }
        }
    }
    if (!used) dep[u] = -1;
    return used;
}
 
int solve() {
    int ans = 0;
    while (BFS()) {
        ans += DFS(S, INF);
    }
    return ans;
}
 
int main() {
//    freopen("input.txt", "r", stdin);
    Init();
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        a[i].input();
        X[++X[0]] = a[i].x[0];
        X[++X[0]] = a[i].x[1];
        Y[++Y[0]] = a[i].y[0];
        Y[++Y[0]] = a[i].y[1];
    }
    X[++X[0]] = 0;
    X[++X[0]] = n;
    Y[++Y[0]] = 0;
    Y[++Y[0]] = n;
    sort(X + 1, X + 1 + X[0]);
    sort(Y + 1, Y + 1 + Y[0]);
    X[0] = unique(X + 1, X + 1 + X[0]) - X - 1;
    Y[0] = unique(Y + 1, Y + 1 + Y[0]) - Y - 1;
    S = 0, T = X[0] + Y[0] + 1;
    for (int i = 1; i < X[0]; ++i) {
        addedge(S, i, X[i + 1] - X[i]);
    }
    for (int i = 1; i < Y[0]; ++i) {
        addedge(X[0] + i, T, Y[i + 1] - Y[i]);
    }
    for (int i = 1; i < X[0]; ++i) {
        for (int j = 1; j < Y[0]; ++j) {
            bool flag = false;  
            for (int k = 1; k <= m; ++k) {
                if (a[k].x[0] <= X[i] && X[i + 1] <= a[k].x[1] && a[k].y[0] <= Y[j] && Y[j + 1] <= a[k].y[1]) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
			//	cout << i << " " << X[0] + j << endl;
                addedge(i, X[0] + j, INF);
            }
        }
    }
    printf("%d\n", solve());
    return 0;
}
