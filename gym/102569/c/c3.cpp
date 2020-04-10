#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
using ll = long long;
using pII = pair<int, int>;
const int N = 3e5 + 10;
int n, x[N], y[N]; ll K;

int a[N];

struct Hash {
	int a[N];
	int size() { return *a; }
	void init() { *a = 0; }
	void add(int x) { a[++*a] = x; }
	void gao() { sort(a + 1, a + 1 + *a); *a = unique(a + 1, a + 1 + *a) - a - 1; }
	int get(int x) { return lower_bound(a + 1, a + 1 + *a, x) - a; }
}hy;

struct BIT {
	int a[N], n;
	inline void init(int _n) { n = _n; memset(a, 0, sizeof (a[0]) * (n + 5)); }
	inline void update(int x, int v) {
		for (; x <= n; x += x & -x)
			a[x] += v;
	}
	inline int query(int x) {
		int res = 0;
		for (; x; x -= x & -x)
			res += a[x];
		return res;
	}
	inline int query(int l, int r) { return query(r) - query(l - 1); }
}bit;

struct E { 
	int op, x, l, r; 
	inline bool operator < (const E &other) const { 
		if (x == other.x) 
			return op > other.op;
		return x < other.x; 
	}
};

inline int get(int x) { return lower_bound(a + 1, a + 1 + *a, x) - a; }

inline ll calc(int dis) {
	ll res = 0;
	*a = 0;
	for (int i = 1; i <= n; ++i) {
		a[++*a] = y[i];
		a[++*a] = y[i] - dis;
		a[++*a] = y[i] + dis;
	}
	sort(a + 1, a + 1 + *a);
	*a = unique(a + 1, a + 1 + *a) - a - 1;
	int m = *a;
	//hy.size();
	//dbg(m);
	vector <E> vec;
	for (int i = 1; i <= n; ++i) {
		vec.push_back({10, x[i], get(y[i]), 0});	
		int l = get(y[i] - dis), r = get(y[i] + dis); 
		vec.push_back({-1, x[i] - dis - 1, l, r});
		vec.push_back({1, x[i] + dis, l, r});
	}	
	bit.init(m);
	sort(vec.begin(), vec.end());
	for (auto &it : vec) {
		if (it.op == 10) {
			bit.update(it.l, 1);
		} else {
			res += bit.query(it.l, it.r) * it.op;
		}
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
	int l = 0, r = 4e8, res = 0;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (calc(mid) >= K) {
			res = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	printf("%d\n", res);
	return 0;
}
