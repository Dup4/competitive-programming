#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll a, b, m;
ll s[110];
ll bit[110];
ll D = (ll)1e14;
bool ok(int n) {
	for (int i = 1; i <= n; ++i) {
		if (s[i] < 1 || s[i] > D) {
			return false;
		}
	}
	ll tot = s[1];
	for (int i = 2; i <= n; ++i) {
		if (s[i] - tot < 1 && s[i] - tot > m) {
			return false;
		}
	}
	return true;
}

void solve() {
	if (a == b) {
		printf("1 %lld\n", a);
		return;
	}
	for (int i = 2; i <= 50; ++i) {
		s[1] = a;
		ll tot = s[1];
		for (int j = 2; j <= i; ++j) {
			s[j] = tot + 1;
			tot += s[j]; 
		}	
		if (s[i] > b) {
			continue; 
		}
	//	if (i == 4) {
	//		for (int j = 1; j <= i; ++j) {
	//			printf("%lld%c", s[j], " \n"[j == i]);
	//		}
	//	}
		ll remind = b - s[i];
		for (int j = 2; j <= i; ++j) {
			ll now = bit[i - j + 1];
			ll need = remind / now; 
			need = min(need, m - 1); 
			remind -= need * now;
			for (int k = j; k <= i; ++k) {
				s[k] += need * bit[k - j + 1];
			}
		}
		if (remind == 0 && ok(i)) {
			printf("%d", i);
			for (int j = 1; j <= i; ++j) {
				printf(" %lld", s[j]);
			}
			puts("");
			return;
		}
	}
	puts("-1");
}

int main() {
	bit[1] = 1;
	bit[2] = 1;
	for (int i = 3; i <= 55; ++i) {
		bit[i] = bit[i - 1] << 1; 
	}
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld%lld", &a, &b, &m);
		solve();
	}
	return 0;
}
