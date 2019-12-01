#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e3 + 10;
int n, a[N];
unordered_map <int, int> mp;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		mp.clear();
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		ll res = 0;
		for (int i = n; i >= 1; --i) ++mp[a[i]];
		for (int i = 1; i <= n; ++i) {
			--mp[a[i]];
			for (int j = i - 1; j >= 1; --j) {
				int x = 2 * a[i] - a[j];
				if (mp.count(x)) {
					res += mp[x];
				}		
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
