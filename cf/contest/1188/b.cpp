#include <bits/stdc++.h>
using namespace std;

#define N 300010
#define ll long long
int n; ll p, k, a[N];
map <ll, int> mp;

int main() {
	while (scanf("%d%lld%lld", &n, &p, &k) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
			a[i] = (a[i] * a[i] % p * a[i] % p - k + p) % p * a[i] % p;
		}
		sort(a + 1, a + 1 + n);
		mp.clear();
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			if (mp.find(a[i]) != mp.end()) {
				res += mp[a[i]]; 
			}
		//	if (mp.find(p - a[i]) != mp.end()) {
		//		res += mp[p - a[i]];
		//	}
			mp[a[i]]++;
		}
		printf("%lld\n", res);
	}
	return 0;
}
