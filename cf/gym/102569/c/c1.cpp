#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
using ll = long long;
using pII = pair<int, int>;
const int N = 4e5 + 10;
int n, x[N], y[N]; ll K;
 
struct Hash {
	vector <int> a;
	int& operator[](int x) { return a[x - 1]; }
	int size() { return a.size(); }
	void init() { a.clear(); }
	void add(int x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int get(int x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }	
}hx, hy;
 
struct BIT {
	int a[N], n;
	void init(int _n) { n = _n; memset(a, 0, sizeof (a[0]) * (n + 5)); }
	void update(int x, int v) {
		for (; x < N; x += x & -x)
			a[x] += v;
	}
	int query(int x) {
		int res = 0;
		for (; x; x -= x & -x)
			res += a[x];
		return res;
	}
	int query(int l, int r) { return query(r) - query(l - 1); }
}bit;
 
ll calc(ll dis) {
	ll res = 0;
	hx.init(), hy.init();
	for (int i = 1; i <= n; ++i) {
		hx.add(x[i]);
		hx.add(x[i] - dis - 1);
		hx.add(x[i] + dis);
		hy.add(y[i]);
		hy.add(y[i] - dis);
		hy.add(y[i] + dis);
	}
	hx.gao(); hy.gao();
	int m = max(hx.size(), hy.size());
	vector <vector<int>> mvec(m + 5);
	vector <vector<pII>> del(m + 5), add(m + 5);
	for (int i = 1; i <= n; ++i) {
		mvec[hx.get(x[i])].push_back(hy.get(y[i]));
		int l = hy.get(y[i] - dis), r = hy.get(y[i] + dis); 
		del[hx.get(x[i] - dis - 1)].push_back(pII(l, r));
		add[hx.get(x[i] + dis)].push_back(pII(l, r));
	}	
	bit.init(m);
	for (int i = 1; i <= m; ++i) {
		for (auto &it : mvec[i]) {
			bit.update(it, 1);
		}
		for (auto &it : del[i]) res -= bit.query(it.fi, it.se);
		for (auto &it : add[i]) res += bit.query(it.fi, it.se);
	}
	res -= n;
	res /= 2;
	return res;
}
 
int main() {
	scanf("%d%lld", &n, &K);
	for (int i = 1, _x, _y; i <= n; ++i) {
		scanf("%d%d", &_x, &_y);
		x[i] = _x + _y;
		y[i] = _x - _y;
	}
	ll l = 0, r = 4e8, res = 0;
	while (r - l >= 0) {
		ll mid = (l + r) >> 1;
		//dbg(mid);
		if (calc(mid) >= K) {
			res = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	printf("%lld\n", res);
	return 0;
}
