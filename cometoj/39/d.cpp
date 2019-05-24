#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll f(ll x) {
	while (x >= 10) {
		vector <int> vec;
		while (x) {
			vec.push_back(x % 10);
			x /= 10;
		}
		reverse(vec.begin(), vec.end());
		x = 0;
		for (int i = 0, sze = (int)vec.size(); i < sze - 1; ++i) {
			x = x * 10 + (vec[i] + vec[i + 1]) % 10;
		}
	}
	return x;
}

int main() {
	ll sum = 0;
	for (int i = 1; i <= 1000; ++i) {
		sum += f(i);
		printf("%d %lld %lld\n", i, f(i), sum);
	}
	return 0;
}
