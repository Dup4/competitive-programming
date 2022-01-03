#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	ll a, b;
	while (scanf("%lld%lld", &a, &b) != EOF) {
		ll Min = a * b / gcd(a, b);
		int pos = 0;
		int limit = min(a, min(b, 1000000));
		for (int i = 1; i <= limit; ++i) {
			ll g = gcd(a - i, b - i); 
			ll t = (a + i) * (b + i) / gcd((a + i), (b + i));
			if (t < Min) {
				Min = t;
				pos = i;
			} 
		}
		printf("%d\n", pos);
	}
	return 0;
}
