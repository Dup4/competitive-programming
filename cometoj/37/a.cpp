#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
	ll n; 
	while (scanf("%lld", &n) != EOF) {
		if (n == 1) {
			puts("2");
			continue;
		}
		ll tot = 2; ll day = 2;
		while (tot <= n) {
			ll t = tot / 2;
			++day;
			tot += t;
		}
		printf("%lld\n", day);
	}
	return 0;
}
