#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void getfac(vector <int> &vec, int n) {
	vec.clear();
	for (int i = 1; 1ll * i * i <= n; ++i) {
		if (n % i == 0) {
			vec.push_back(i);
			if (i * i != n)
			vec.push_back(n / i);
		}
	}
}

int main() {
	int n;
	while (scanf("%d", &n) != EOF) {
		vector <int> vec_a;
		getfac(vec_a, n);
		ll res = 1e18;
		for (auto a : vec_a) {
			vector <int> vec_b;
			getfac(vec_b, n / a);
			for (auto &b : vec_b) {
				int c = n / a / b;
				res = min(res, 2ll * (a * b + a * c + b * c));
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
