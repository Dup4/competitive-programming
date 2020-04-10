#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double db;
const int N = 1e4 + 10, INF = 0x3f3f3f3f;
int n, k; ll a[N], ff[N], gg[N], *f, *g;  

namespace DP {
	ll y[N];
	int que[N], head, tail; 
	db slope(int i, int j) { return (y[i] - y[j]) * 1.0 / (a[i + 1] - a[j + 1]); }
	void gao() {
		head = 1, tail = 0;
		que[++tail] = 0;
		f[0] = 0; 
		for (int i = 1; i <= n; ++i) { 
			while (head < tail && slope(que[head], que[head + 1]) <= a[i] * 2) ++head;
			f[i] = g[que[head]] + (a[i] - a[que[head] + 1]) * (a[i] - a[que[head] + 1]);
			y[i] = g[i] + a[i + 1] * a[i + 1]; 
			while (head < tail && slope(que[tail - 1], que[tail]) >= slope(que[tail], i)) --tail;
			que[++tail] = i;
		}
	}
}

int main() {
	int _T; scanf("%d", &_T);
	for (int kase = 1; kase <= _T; ++kase) { 
		printf("Case %d: ", kase);
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
		sort(a + 1, a + 1 + n);
		f = ff, g = gg;
		g[0] = 0;
		for (int i = 1; i <= n; ++i) {
			g[i] = (a[i] - a[1]) * (a[i] - a[1]);
		}
		--k;
		while (k--) {
			DP::gao();
			swap(f, g);
		}
		printf("%lld\n", g[n]);
	}
	return 0;
}
