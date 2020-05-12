#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pLI pair<ll, int>
#define fi first
#define se second
#define SZ(x) (int((x).size()))
const int N = 3e5 + 10;
const ll INF = 1e18; 
int n, m;

struct E {
	int u, v; ll w;
	bool operator < (const E &other) const { return w < other.w; }
};

vector <E> e[2];

struct UFS {
	int fa[N], rk[N];
	void init(int n) {
		memset(fa, 0, sizeof (fa[0]) * (n + 5));
		memset(rk, 0, sizeof (rk[0]) * (n + 5));
	}
	int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
	bool merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) {
			if (rk[fx] > rk[fy]) swap(fx, fy);
			fa[fx] = fy;
			if (rk[fx] == rk[fy]) ++rk[fy];
			return true;
		}
		return false;
	}
	bool same(int x, int y) { return find(x) == find(y); }
}ufs;

ll gao(int x) {
	ufs.init(n);
	for (int i = 0; i < SZ(e[1]); ++i) {
		int u = e[1][i].u, v = e[1][i].v;
		if (u != x && v != x) ufs.merge(u, v);
	}
	ll res = 0;
	for (int i = 0; i < SZ(e[0]); ++i) {
		int u = e[0][i].u, v = e[0][i].v; ll w = e[0][i].w;	
		if (u != x && v != x && ufs.merge(u, v))
			res += w;
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++i) if (i != x) {
		if (ufs.fa[i] == 0) ++cnt;
	}
	if (cnt > 1) return INF;
	return res;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, sta; i <= m; ++i) {
		E tmp;
		scanf("%d%d%lld%d", &tmp.u, &tmp.v, &tmp.w, &sta);
		e[sta].push_back(tmp);
	}
	sort(e[0].begin(), e[0].end());
	sort(e[1].begin(), e[1].end());
	vector <pLI> vec;
	for (int i = 1; i <= n; ++i) {
		vec.push_back(pLI(gao(i), i));
	}
	sort(vec.begin(), vec.end(), [&](pLI x, pLI y) { return x.fi > y.fi; });
	if (vec[0].fi == 0) printf("0\n");
	else {
		vector <int> res;
		for (int i = 0; i < n; ++i) {
			if (i && vec[i].fi < vec[i - 1].fi) break;
			res.push_back(vec[i].se);
		}
		sort(res.begin(), res.end());
		for (int i = 0; i < SZ(res); ++i) 
			printf("%d%c", res[i], " \n"[i == SZ(res) - 1]);
	}
	return 0;
}
