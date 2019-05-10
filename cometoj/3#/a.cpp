#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 510
int n, k, a[N];

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		ll res = 0;
		vector <ll> vec;
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				vec.push_back(a[i] + a[j]);
			}
		}
		sort(vec.begin(), vec.end(), [&](ll x, ll y) {
			return x > y;
		});
		for (auto it : vec) {
			if (k == 0) {
				break;
			}
			--k;
			res += it;
		}
		printf("%lld\n", res);
	}
	return 0;
}
