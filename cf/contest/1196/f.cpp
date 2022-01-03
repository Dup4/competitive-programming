#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n, m, k;
struct Edge {
	int u, v, w;
	Edge() {}
	void scan() {
		scanf("%d%d%d", &u, &v, &w);
	}
	bool operator < (const Edge &other) const {
		return w < other.w; 
	}
}e[N];
struct Hash {
	int a[N], cnt;
	Hash() { cnt = 0; }
	void add(int x) {
		a[++cnt] = x;
	}
	void work() {
		sort(a + 1, a + 1 + cnt);
		cnt = unique(a + 1, a + 1 + cnt) - a - 1;
	}
	int get(int x) {
		return lower_bound(a + 1, a + 1 + cnt, x) - a;
	}
}hs;
ll f[810][810];

void Floyd(int n) {
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
			}
		}
	}
}

int main() {
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		for (int i = 1; i <= m; ++i) e[i].scan();
		sort(e + 1, e + 1 + m);
		hs = Hash();
		for (int i = 1; i <= k; ++i) {
			hs.add(e[i].u);
			hs.add(e[i].v);
		}
		hs.work();
		memset(f, 0x3f, sizeof f);
		for (int i = 1; i <= k; ++i) {
			int u = hs.get(e[i].u);
			int v = hs.get(e[i].v);
			f[u][v] = e[i].w;
			f[v][u] = e[i].w; 
		}
		int tot = hs.cnt;
		Floyd(tot);
		vector <ll> vec;
		for (int i = 1; i <= tot; ++i)
			for (int j = i + 1; j <= tot; ++j) {
				vec.push_back(f[i][j]);
			}
		sort(vec.begin(), vec.end());
		printf("%lld\n", vec[k - 1]);
	}
	return 0;
}
