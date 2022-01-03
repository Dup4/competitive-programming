#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = 998244353;
int n, a[N], len;

int getlen(int x) {
	int res = 0;
	while (x) {
		++res;
		x /= 10;
	}
	return res;
}

ll f(ll x) {
	ll tot = 0;
	vector <int> vec;
	while (x) {
		vec.push_back(x % 10);
		x /= 10;
	}
	reverse(vec.begin(), vec.end());
	for (auto it : vec) {
		tot = tot * 10 + it;
		tot = tot * 10 + it;
		tot %= p;	
	}
	return tot * n % p; 
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		len = getlen(a[1]);
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			res += f(a[i]);
			res %= p;
		}
		printf("%lld\n", res);
	}
	return 0;
}
