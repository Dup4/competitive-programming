#include <bits/stdc++.h>
using namespace std;

#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }

struct Min_Cost_Max_Flow {
	static const int N = 5e3 + 10;
	static const int M = 5e4 + 10;
	static const int INF = 0x3f3f3f3f;
	struct E { int to, nx, cap, flow, cost; }edge[M << 1]; int head[N], tot;
	int pre[N], dis[N]; 
	bool vis[N];
	int n;
	void init(int _n) {
		n = _n;
		tot = 0;
		memset(head, -1, sizeof head);
	}
	void addedge(int u, int v, int cap, int cost) {
		edge[tot] = { v, head[u], cap, 0, cost}; head[u] = tot++;
		edge[tot] = { u, head[v], 0, 0, -cost}; head[v] = tot++;
	}
	bool spfa(int s, int t) {
		queue <int> q;
		for (int i = 1; i <= n; ++i) {
			dis[i] = INF;
			vis[i] = false;
			pre[i] = -1;
		}
		dis[s] = 0;
		vis[s] = true;
		q.push(s);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			vis[u] = false;
			for (int i = head[u]; i != -1; i = edge[i].nx) {
				int v = edge[i].to;
				if (edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost) {
					dis[v] = dis[u] + edge[i].cost;
					pre[v] = i;
					if (!vis[v]) {
						vis[v] = true;
						q.push(v);
					}
				}
			}
		}
		if (pre[t] == -1) return false;
		return true;
	}
	//返回flow cost引用传递
	//点的编号从1开始
	int gao(int s, int t, int &cost) {
		int flow = 0;
		cost = 0;
		while (spfa(s, t)) {
			int Min = INF;
			for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
				if (Min > edge[i].cap - edge[i].flow) {
					Min = edge[i].cap - edge[i].flow;
				}
			}
			for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
				edge[i].flow += Min;
				edge[i ^ 1].flow -= Min;
				cost += edge[i].cost * Min;
			}
			flow += Min;
		}
		return flow;
	}
}MCMF;

const int N = 1e3 + 10;
int n, cnt[110][220], tot[220], need[220]; char s[N], t[N];

int main() {
	scanf("%s", s + 1);
	scanf("%d", &n);
	for (int i = 1; s[i]; ++i) ++need[s[i]];
	for (int i = 1; i <= n; ++i) {
		scanf("%s", t + 1);
		for (int j = 1; t[j]; ++j) {
			++cnt[i][t[j]];
			++tot[t[j]];
		}
	}
	int gap = 0;
	for (int i = 1; i < 220; ++i) {
		gap += max(0, need[i] - tot[i]);
	}
	if (gap > 0) {
		printf("No %d\n", gap);
	} else {
		int S = 1, T = 2;
		MCMF.init(1e3);
		for (int i = 1; i < 220; ++i) {
			if (need[i]) {
				dbg(T + n + i, need[i]);
				MCMF.addedge(T + n + i, T, need[i], 0);
			}
		}
		for (int i = 1; i <= n; ++i) { 
			MCMF.addedge(S, T + i, MCMF.INF, 1);
			for (int j = 1; j < 220; ++j) {
				if (cnt[i][j] && need[j]) {
					dbg(i, T + n + j, cnt[i][j]);
					MCMF.addedge(T + i, T + n + j, cnt[i][j], 0);
				}
			}
		}
		int cost = 0;
		dbg(MCMF.gao(S, T, cost));
		printf("Yes %d\n", cost);
	}
	return 0;
}
