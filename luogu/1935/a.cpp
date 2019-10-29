#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
const int N = 110;
int n, m, col[N][N], A[N][N], B[N][N], C[N][N];
inline int id(int x, int y) { return (x - 1) * m + y; }
int Move[][2] = {
	{0, 1},
	{0, -1},
	{1, 0},
	{-1, 0}
};
inline bool ok(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m) return false;
	return true;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		dicnic.init();
		int S = n * m + 1, T = S + 1;
		ll tot = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (i == 1 && j == 1) col[i][j] = 1;
				else if (j > 1) col[i][j] = col[i][j - 1] ^ 1;
				else if (i > 1) col[i][j] = col[i - 1][j] ^ 1;
			}
		}
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) scanf("%d", A[i] + j);
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) scanf("%d", B[i] + j);
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) scanf("%d", C[i] + j);
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
			tot += A[i][j] + B[i][j];
			if (col[i][j] == 1) {
				dicnic.addedge(S, id(i, j), A[i][j]);
				dicnic.addedge(id(i, j), T, B[i][j]);
			} else {
				dicnic.addedge(S, id(i, j), B[i][j]);
				dicnic.addedge(id(i, j), T, A[i][j]);
			}
		}
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
			for (int k = 0; k < 4; ++k) {
				int x = i + Move[k][0];
				int y = j + Move[k][1];
				if (ok(x, y)) {
					dicnic.addedge(id(i, j), id(x, y), C[i][j]);
					tot += C[i][j];
				}
			}
		}
		dicnic.set(S, T);
		printf("%lld\n", tot - dicnic.solve());
	}
	return 0;
}





