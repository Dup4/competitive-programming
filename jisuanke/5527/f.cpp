#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll p = 998244353;

int n;

int main() {
	while (cin >> n) {
		ll res = 0;
		for (int a = 2; a <= n; ++a) {
			ll sum = 0;
			for (int b = a; b <= n; ++b) {
				sum += floor(log(b) / log(a)) * ceil(log(a) / log(b));
				sum %= p;
			}
			sum *= a;
			sum %= p;
			res += sum;
			res %= p;
		}
		cout << res << endl;
	}
	return 0;
}
