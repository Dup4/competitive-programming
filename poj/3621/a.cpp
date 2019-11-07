#include <cstdio>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;
#define db double
const int N = 1e3 + 10;
const db eps = 1e-8;
struct E { int to, nx, w; db nw; }e[N * 5]; int h[N];
void addedge(int u, int v, int w) { e[++*h] = { v, h[u], w, 0}; h[u] = *h; }
int n, m, a[N];

struct SPFA {
	int Insta[N], cnt[N];
	db dis[N];
	bool gao(db r) {
		memset(Insta, 0, sizeof Insta);
		memset(cnt, 0, sizeof cnt);
		memset(dis, 0, sizeof dis);
		for (int i = 1; i <= m; ++i) {
			e[i].nw = r * e[i].w - a[e[i].to];
		}
		queue <int> que;
		//避免多次SPFA
		for (int i = 1; i <= n; ++i) {
			que.push(i);
		}
		//适当剪枝
		int limit = max(10, n / 3); 
		while (!que.empty()) {
			int u = que.front(); que.pop();
			Insta[u] = 0;
			for (int i = h[u]; i; i = e[i].nx) {
				int v = e[i].to;
				if (dis[v] > dis[u] + e[i].nw) {
					dis[v] = dis[u] + e[i].nw;
					if (Insta[v] == 0) {
						que.push(v);
						Insta[v] = 1;
						++cnt[v];
						if (cnt[v] >= limit) {
							return true;
						}
					}
				}
			}
		}
		return false;
	}
}spfa;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(h, 0, sizeof h);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			addedge(u, v, w);
		}
		db l = 0, r = 1e7, ans = -1;
		while (fabs(r - l) > eps) {
			db mid = (l + r) / 2;
			if (spfa.gao(mid)) {
				l = mid;
				ans = mid;
			} else {
				r = mid;
			}
		}
		printf("%.2f\n", ans);
	}
	return 0;
}
