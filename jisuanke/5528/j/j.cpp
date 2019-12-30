#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 4e2 + 10;
int n; ll a[N], p[N], b[N], c[N];
struct KM {
	static const int N = 4e2 + 10;
	static const int INF = 0x3f3f3f3f;
	int lx[N], ly[N], slack[N], w[N][N]; //以上为权值类型
	int vx[N], vy[N], pre[N], left[N], right[N], nl, nr, n;
	void match(int& u) {
		for (; u; swap(u, right[pre[u]])) 
			left[u] = pre[u];
	}
	void bfs(int u) {
		static int q[N], front, rear;
		front = 0; vx[q[rear = 1] = u] = true;
		while (true) {
			while (front < rear) {
				int u = q[++front];
				for (int v = 1; v <= n; ++v) {
					int tmp; 
					if (vy[v] || (tmp = lx[u] + ly[v] - w[u][v]) > slack[v])
						continue;
					pre[v] = u;
					if (!tmp) {
						if (!left[v]) return match(v);
						vy[v] = vx[q[++rear] = left[v]] = true;
					} else {
						slack[v] = tmp;
					}
				}
			}
			int a = INF;
			for (int i = 1; i <= n; ++i) {
				if (!vy[i] && a > slack[i]) a = slack[u = i];
			}
			for (int i = 1; i <= n; ++i) {
				if (vx[i]) lx[i] -= a;
				if (vy[i]) ly[i] += a;
				else slack[i] -= a;
			}
			if (!left[u]) return match(u);
			vy[u] = vx[q[++rear] = left[u]] = true;
		}
	}
	void exec() {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				slack[j] = INF;
				vx[j] = vy[j] = false;
			}
			bfs(i);
		}
	}
	void init(int _nl, int _nr) {
		nl = _nl, nr = _nr;
		n = max(nl, nr);
		for (int u = 1; u <= n; ++u) {
			lx[u] = ly[u] = 0;
			left[u] = right[u] = 0;
			for (int v = 1; v <= n; ++v) {
				w[u][v] = 0;
			}
		}
	}
	ll work() {
		for (int u = 1; u <= n; ++u) {
			for (int v = 1; v <= n; ++v) {
				lx[u] = max(lx[u], w[u][v]);
			}
		}
		exec();
		ll ans = 0;
		for (int i = 1; i <= n; ++i) {
			ans += lx[i] + ly[i];
		}
		return ans;
	}
	void output() {
		for (int i = 1; i <= nl; ++i) {
			printf("%d%c", (w[i][right[i]] ? right[i] : 0), " \n"[i == nl]);
		}
	}
}km;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
		for (int i = 1; i <= n; ++i) scanf("%lld", p + i);
		for (int i = 1; i <= n; ++i) scanf("%lld", b + i);
		for (int i = 1; i <= n; ++i) scanf("%lld", c + i);
	    sort(b + 1, b + 1 + n, [&](ll x, ll y) { return x < y; });	
	    sort(c + 1, c + 1 + n, [&](ll x, ll y) { return x > y; });	
		km.init(n, n);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				int w = 0;
				for (int k = 1; k <= n; ++k) {
					if (b[i] + c[j] > a[k]) 
						w += p[k];
				}
				km.w[i][j] = w; 
			}
		}
		printf("%lld\n", km.work());
	}
	return 0;
}