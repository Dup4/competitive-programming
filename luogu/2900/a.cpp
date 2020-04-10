#include <bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int, int> pII;
#define fi first
#define se second
const int N = 1e5 + 10;
int n; pII a[N];

namespace DP {
	ll f[N];
	int que[N], head, tail;
	db slope(int i, int j) { return 1ll * (f[i] - f[j]) / (a[j + 1].fi - a[i + 1].fi); }
	void gao() {
		memset(f, 0, sizeof f);
		head = 1, tail = 0;
		que[++tail] = 0;
		for (int i = 1; i <= n; ++i) {
			while (head < tail && slope(que[head], que[head + 1]) <= a[i].se) ++head;
			f[i] = f[que[head]] + 1ll * a[que[head] + 1].fi * a[i].se;
			while (head < tail && slope(que[tail - 1], que[tail]) >= slope(que[tail], i)) -- tail;
			que[++tail] = i;
		}
		printf("%lld\n", f[n]);
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i].fi, &a[i].se);
		sort(a + 1, a + 1 + n, [&](pII a, pII b) {
			if (a.fi != b.fi)
				return a.fi > b.fi;
			return a.se > b.se;		
		});
		int _n = 1;
		for (int i = 2; i <= n; ++i) {
			if (a[i].se > a[_n].se)
				a[++_n] = a[i];	
		}
		n = _n;
		DP::gao();
	}
	return 0;
}
