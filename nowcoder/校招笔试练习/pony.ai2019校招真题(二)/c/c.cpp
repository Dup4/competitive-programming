#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 10;
int n; ll K;

struct BIT {
	int a[N];
	void init() { memset(a, 0, sizeof (a[0]) * (n + 10)); }
	void update(int x, int v) { for (; x <= n; a[x] += v, x += x & -x); }
	int query(int x) { int res = 0; for (; x > 0; res += a[x], x -= x & -x); return res; }
}bit;

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%lld%d", &K, &n);
		bit.init();
		vector <int> vec[10];
		vector <int> res; 
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			vec[x].push_back(i);
		}
		for (int i = 0; i < 10; ++i) reverse(vec[i].begin(), vec[i].end());
		for (int i = 1; i <= n; ++i) { 
			int it = 0;
			for (int j = 9; j >= 0; --j) if (!vec[j].empty()) {
				int ori = vec[j].back();
				int diff = ori - bit.query(ori) - 1;
				if (diff <= K) {
					K -= diff;
					vec[j].pop_back();
					it = j;
					bit.update(ori, 1);
					break;
				}
			}
			res.push_back(it);
		}
		if (K & 1) swap(res[n - 1], res[n - 2]);
		for (int i = 0; i < n; ++i)
			printf("%d%c", res[i], " \n"[i == n - 1]);
	}
	return 0;
}
