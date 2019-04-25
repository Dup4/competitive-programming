#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, p, a[N];
multiset <int> s;

int main() {
	int T; cin >> T;
	while (T--) {
		s.clear();
		scanf("%d%d", &n, &p);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			a[i] %= p;
		}
		int res = 0;
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++i) {
			auto it = s.upper_bound(p - a[i] - 1);
			if (it != s.begin()) {
				--it;
				res = max(res, a[i] + *it);
			}
			s.insert(a[i]);
		}
		for (int i = 1; i < n; ++i) {
			res = max(res, (a[i] + a[n]) % p);
		}
		printf("%d\n", res);
	}
	return 0;
}
