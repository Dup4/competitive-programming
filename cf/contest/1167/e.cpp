#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
int n, m;
int a[N], l[N], r[N];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(l, 0, sizeof l);
		memset(r, 0, sizeof r);
		vector <int> vec;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			if (l[a[i]] == 0) {
				l[a[i]] = i;
			}
			r[a[i]] = i;
			vec.push_back(a[i]);
		}
		l[m + 1] = n + 1;
		for (int i = 1; i <= m; ++i) {
			if (r[i] == 0) {
				r[i] = r[i - 1];
			}
		}
		for (int i = m; i >= 1; --i) {
			if (l[i] == 0) {
				l[i] = l[i + 1];
			}
		}
		sort(vec.begin(), vec.end());
		vec.erase(unique(vec.begin(), vec.end()), vec.end());
		int x = -1, y = -1;
		int sze = (int)vec.size();
		for (int i = 1; i < sze; ++i) {
			if (l[vec[i]] < r[vec[i - 1]]) {
				x = vec[i];
				break;
			}
		}
		for (int i = sze - 2; i >= 0; --i) {
			if (r[vec[i]] > l[vec[i + 1]]) {
				y = vec[i];
				break;
			}
		}
		if (x == -1) {
			printf("%lld\n", 1ll * m * (m + 1) / 2);
		} else {
			ll ans = 0;
			for (int i = m; i >= y; --i) {
				while (r[x - 1] > l[i + 1]) --x;
				ans += x;
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}
