#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, m;
ll v[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", v + i);
			v[i] += v[i - 1];
		}
		ll res = 0;
		vector <ll> vec;
		for (int i = 1, l, r; i <= m; ++i) {
			scanf("%d%d", &l, &r);
			vec.push_back(v[r] - v[l - 1]);
		}
		sort(vec.begin(), vec.end());
		for (int i = 0; i < m; ++i) {
			res += 1ll * (i + 1) * vec[i];
		}
		printf("%lld\n", res);
	}
	return 0;
}
