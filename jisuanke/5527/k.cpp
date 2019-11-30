#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>; 
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
void err() { cout << "\033[39;0m" << endl; }
template <class T, class... Ts>
void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 1e3 + 10, INF = 0x3f3f3f3f;
int n, m, a[N][N], b[N][N], l[N][N], r[N][N], num[N][N];
pII c[N], id[N * N];

struct CT {
	struct node {
		int id, val, fa;
		int son[2];
		node() {}
		node (int id, int val, int fa) : id(id), val(val), fa(fa) {
			son[0] = son[1] = 0;
		}
		bool operator < (const node &other) const {
			return val < other.val;
		}
	}t[N];
	int root;
	void init() {
		t[0] = node(0, -INF, 0);
	}
	void build(int n, int *a) {
		for (int i = 1; i <= n; ++i) {
			t[i] = node(i, a[i], 0);
		}
		for (int i = 1; i <= n; ++i) {
			int k = i - 1;
			while (t[i] < t[k]) {
				k = t[k].fa;
			}
			t[i].son[0] = t[k].son[1];
			t[k].son[1] = i;
			t[i].fa = k;
			t[t[i].son[0]].fa = i;
		}
		root = t[0].son[1];
	}
	int dfs(int u) {
		if (!u) return 0;
		c[u].fi = dfs(t[u].son[0]);
		c[u].se = dfs(t[u].son[1]);
		return c[u].fi + c[u].se + 1;
	}
}ct;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &a[i][j]);
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &b[i][j]);
				id[b[i][j]] = pII(i, j); 
			}
		}

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (j == 1) {
					l[i][j] = j;
				} else {
					int pre = a[i][j - 1], now = a[i][j];
					if (id[pre].fi == id[now].fi && id[pre].se == id[now].se - 1) {
						l[i][j] = l[i][j - 1];
					} else {
						l[i][j] = j;
					}
				}
			}
			for (int j = m; j >= 1; --j) {
				if (j == m) {
					r[i][j] = j;
				} else {
					int nx = a[i][j + 1], now = a[i][j];
					if (id[nx].fi == id[now].fi && id[nx].se == id[now].se + 1) {
						r[i][j] = r[i][j + 1];
					} else {
						r[i][j] = j;
					}
				}
			}
		}
		for (int j = 1; j <= m; ++j) {
			for (int i = 1; i <= n; ++i) {
				if (i == 1) {
					num[i][j] = 1;
				} else {
					int pre = a[i - 1][j], now = a[i][j];
					if (id[pre].fi == id[now].fi - 1 && id[pre].se == id[now].se) {
						num[i][j] = num[i - 1][j] + 1;
					} else {
						num[i][j] = 1;
					}
				}
			}
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
		//	for (int j = 1; j <= m; ++j) {
		//		dbg(i, j, l[i][j], r[i][j], num[i][j]);
		//	}
			ct.init();
			ct.build(n, num[i]);
			ct.dfs(ct.root);
			for (int j = 1; j <= m; ++j) {
				int tl = max(l[i][j], j - c[j].fi);
				int tr = min(r[i][j], j + c[j].se);
				res = max(res, (tr - tl + 1) * num[i][j]);
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
