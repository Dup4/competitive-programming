#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, M1, M2, Maxk;
int tot, head[N];
int dis[N], inq[N], cnt[N];
int que[N], ql, qr;

struct Edge {
	int to, nxt, w;
	Edge() {}
	Edge(int to, int nxt, int w): to(to), nxt(nxt), w(w) {}
}edge[N << 1];

struct node {
	int l, r, k;
	void input() {
		scanf("%d %d %d", &l, &r ,&k);
		Maxk = max(Maxk, k);
	}
}q1[N], q2[N];

inline void Init() {
	for (int i = 0; i <= n; ++i) {
		inq[i] = 0, cnt[i] = 0, dis[i] = INF;
	}
}

inline void addedge(int u, int v, int w) {
	edge[tot] = Edge(v, head[u], w); head[u] = tot++;
}

bool SPFA(int x) {
	dis[0] = 0;
	inq[0] = 1;
	ql = 1, qr = 0;
	que[++qr] = 0;
	while (ql <= qr) {
		int u = que[++ql];
		inq[u] = 0;
		for (int i = head[u]; ~i; i = edge[i].nxt) {
			int v = edge[i].to, w = edge[i].w;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				if (!inq[v]) {
					inq[v] = 1;
					que[++qr] = v;
					if (++cnt[v] > n) return false;
				}
			}
		}
	}
	return dis[n] == x;
}

bool check(int x) {
	Init();
	for (int i = 1; i <= M2; ++i) {
		edge[i - 1].w = x - q2[i].k;
	}
	edge[tot - 1].w = -x;
	edge[tot - 2].w = x;
	return SPFA(x);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &n, &M1, &M2);
		Maxk = 0; 
		for (int i = 1; i <= M1; ++i) q1[i].input();
		for (int i = 1; i <= M2; ++i) q2[i].input();
		for (int i = 0; i <= n; ++i) head[i] = -1; tot = 0;
		for (int i = 1; i <= M2; ++i) {
			int l = q2[i].l - 1, r = q2[i].r;
			addedge(l, r, 0);
		}
		for (int i = 1; i <= M1; ++i) {
			int l = q1[i].l - 1, r = q1[i].r, k = q1[i].k;
			addedge(r, l, -k);
		}
		for (int i = 1; i <= n; ++i) {
			addedge(i, i - 1, 0);
			addedge(i - 1, i, 1);
		}
		addedge(0, n, 0); 
		addedge(n, 0, 0); 
		int l = Maxk, r = n - 1, res = n;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				r = mid - 1;
				res = mid;
			} else {
				l = mid + 1;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
