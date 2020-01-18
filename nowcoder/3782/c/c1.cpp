#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e6 + 10;
int n, m, a[N], b[N], f[N], g[N];

struct BIT {
	int a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			a[x] = max(a[x], v);
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res = max(res, a[x]);
		}
		return res;
	}
	void update1(int x, int v) {
		for (; x > 0; x -= x & -x)
			a[x] = max(a[x], v);
	}
	int query1(int x) {
		int res = 0;
		for (; x < N; x += x & -x) 
			res = max(res, a[x]);
		return res;
	}
	void clear(int x) {
		for (; x > 0; x -= x & -x)
			a[x] = 0;
	}
}bit;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), b[i] = a[i];
		sort(b + 1, b + 1 + n); 
		m = unique(b + 1, b + 1 + n) - b - 1;
		for (int i = 1; i <= n; ++i)
			a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b; 
		bit.init();
		for (int i = 1; i <= n; ++i) {
			f[i] = bit.query(a[i]) + 1;
			bit.update(a[i], f[i]);
		}
		int res = bit.query(N - 1);
		vector <vector<pII>> vec(res + 10);
		for (int i = 1; i <= n; ++i) {
			vec[f[i]].push_back(pII(i, a[i]));
		}
		bit.init(); 
		memset(g, 0, sizeof g);
		vec[res + 1].push_back(pII(n + 1, m + 1));
		bit.update1(m + 1, n + 1); 
		for (int i = res; i >= 1; --i) {
			vector <pII> tmp;
			for (auto &it : vec[i]) {
				if (it.fi < bit.query1(it.se)) {
					tmp.push_back(it);
				} 
			}
			if (tmp.size() == 1) {
				g[tmp[0].fi] = 1;
			}
			for (auto &it : vec[i + 1]) {
				bit.clear(it.se);
			}
			for (auto &it : tmp) {
				bit.update1(it.se, it.fi);
			}
			vec[i] = tmp; 
		}
		for (int i = 1; i <= n; ++i)
			printf("%d%c", res - g[i], " \n"[i == n]);
	}
	return 0;
}
