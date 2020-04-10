#include <bits/stdc++.h>
using namespace std;
const int N = 3e3 + 10, INF = 0x3f3f3f3f;
int n, m;

struct Graph {
	struct E { int to, nx, w; }e[N << 1]; int h[N], cnt;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v, int w = 0) { e[++cnt] = { v, h[u], w}; h[u] = cnt; } 
}G;

namespace SPFA {
	int dis[N], cnt[N], inQue[N], que[N], head, tail; 
	bool gao(int st) {
		for (int i = 1; i <= n; ++i) {
			dis[i] = INF;
			inQue[i] = 0;
			cnt[i] = 0;
		}
		inQue[st] = 1;
		dis[st] = 0;
		cnt[st] = 1;
		head = tail = 0;
		que[tail++] = st;
		while (head != tail) {
			int u = que[head]; head = (head + 1) % N;
			inQue[u] = 0;
			for (int i = G.h[u]; ~i; i = G.e[i].nx) {
				int v = G.e[i].to, w = G.e[i].w;
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					if (inQue[v] == 0) {
						inQue[v] = 1;
						++cnt[v];
						if (cnt[v] >= n) return true;
						que[tail] = v;
						if (dis[que[head]] > dis[que[tail]]) swap(que[head], que[tail]);
						tail = (tail + 1) % N; 
					}
				}
			}
		}
		return false;
	}
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &m);
		G.init(n);
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G.addedge(u, v, w);
			if (w >= 0) G.addedge(v, u, w);
		}
		if (SPFA::gao(1)) puts("YE5");
		else puts("N0");
	}
	return 0;
}
