#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n, m;
struct Dicnic {
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
	vector <int> res;
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
}dicnic;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		dicnic.init();
		int S = n + m + 1, T = S + 1, tot = 0;
		for (int i = 1, b; i <= m; ++i) {
			scanf("%d", &b);
			dicnic.addedge(i, T, b);
		}
		for (int i = 1, a, k; i <= n; ++i) {
			scanf("%d%d", &a, &k);
			dicnic.addedge(S, i + m, a);
			for (int j = 1, x; j <= k; ++j) {
				scanf("%d", &x);
				dicnic.addedge(i + m, x, 1e9);
			}
			tot += a;
		}
		dicnic.set(S, T);
		printf("%lld\n", 1ll * tot - dicnic.solve());
	}
	return 0;
}



