#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n, l, r;
ll bit[65];    
ll f(ll x) {
	ll tot = 0;
	for (int i = 63; i >= 0; --i) {
		if ((x >> i) & 1) {
			int t = 0;
			for (int j = i - 1; j >= 0; --j) {
				t += ((n >> j) & 1);  
			}
			tot += bit[t];
			if (((n >> i) & 1) == 0) {  
				--tot;
				break; 
			}
		}
	} 
	return x - tot; 
}

int main() {
	bit[0] = 1;
	for (int i = 1; i < 64; ++i) {
		bit[i] = bit[i - 1] << 1; 
	}
	while (scanf("%lld%lld%lld", &n, &l, &r) != EOF) {
		printf("%lld\n", f(r) - f(l - 1));
	}
	return 0;
}
