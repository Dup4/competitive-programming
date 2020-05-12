#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
int n, a[N], f[N], g[N];

struct Hash {
	vector <int> a;
	int& operator[](int x) { return a[x - 1]; }
	int size() { return a.size(); }
	void init() { a.clear(); }
	void add(int x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int get(int x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }	
}hs;

struct BIT {
	int a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x < N; x += x & -x)
			a[x] = max(a[x], v);
	}
	int query(int x) {
		if (x < 0) return 0;
		int res = 0;
		for (; x; x -= x & -x)
			res = max(res, a[x]);
		return res;
	}
}bit;

void gao(int *f) {
	bit.init();
	for (int i = 1; i <= n; ++i) {
		f[i] = 1 + bit.query(a[i] - 1);
		bit.update(a[i], f[i]);
	}
}

int main() {
	scanf("%d", &n);
	hs.init();
	for (int i = 1; i <= n; ++i) scanf("%d", a + i), hs.add(a[i]);
	hs.gao();
	for (int i = 1; i <= n; ++i) a[i] = hs.get(a[i]);
	gao(f);
	reverse(a + 1, a + 1 + n);
	gao(g);
	reverse(a + 1, a + 1 + n);
	reverse(g + 1, g + 1 + n);
	int maxLen = -1, pos = -1, dif = 0;
	for (int i = 2; i < n; ++i) {
		if (f[i] > 1 && g[i] > 1) {
			if ((f[i] + g[i] - 1 > maxLen) || 
				(f[i] + g[i] - 1 == maxLen && abs(f[i] - g[i]) < dif)) {
					maxLen = f[i] + g[i] - 1;
					dif = abs(f[i] - g[i]);
					pos = i;
				}
		}
	}
	if (maxLen == -1) puts("No peak shape");
	else printf("%d %d %d\n", maxLen, pos, hs[a[pos]]);
	return 0;
}
