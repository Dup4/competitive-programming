#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct Dinic {
	static const int M = 2e6 + 10;
	static const int N = 1e5 + 10;
	static const ll INFLL = 0x3f3f3f3f3f3f3f3f;
	struct Edge {
        int to, nxt;
        ll flow;
        Edge() {}
        Edge(int to, int nxt, ll flow) : to(to), nxt(nxt), flow(flow) {}
    } edge[M];
	int S, T;
    int head[N], tot;
    int dep[N];
    void init() {
        memset(head, -1, sizeof head);
        tot = 0;
    }
	void set(int S, int T) {
		this->S = S;
		this->T = T;
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
    ll DFS(int u, ll f) {
        if (u == T || f == 0) return f;
        ll w, used = 0;
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            if (edge[i].flow && dep[edge[i].to] == dep[u] + 1) {
                w = DFS(edge[i].to, min(f - used, edge[i].flow));
                edge[i].flow -= w;
                edge[i ^ 1].flow += w;
                used += w;
                if (used == f) return f;
            }
        }
        if (!used) dep[u] = -1;
        return used;
    }
    ll solve() {
        ll ans = 0;
        while (BFS()) {
            ans += DFS(S, INFLL);
        }
        return ans;
    }
}dinic;

int n, m, id, e[200100][3], S, T, W;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d%d", e[i], e[i] + 1, e[i] + 2);
		}
		scanf("%d%d%d", &S, &T, &W); 
		int res = 0;
		dinic.init(); dinic.set(S, T);
		for (int i = 1; i <= m; ++i) {
			int u = e[i][0], v = e[i][1], w = e[i][2];
			if (w < W) {  
				dinic.addedge(u, v, 1);
				dinic.addedge(v, u, 1);
			}
		}
		res += dinic.solve();
		dinic.init(); dinic.set(S, T);
		for (int i = 1; i <= m; ++i) {
			int u = e[i][0], v = e[i][1], w = e[i][2]; 
			if (w > W) {
				dinic.addedge(u, v, 1);
				dinic.addedge(v, u, 1);
			}
		}
		res += dinic.solve();
		printf("%d\n", res);
	}
	return 0;
}

