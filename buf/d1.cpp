#include <bits/stdc++.h>
using namespace std;
 
const int mod = 998244353;

int main() {
	int res = 0;
	for (int i = 1; i != 10000000; ++i) {
		res += 1ll * i * i % mod * i % mod * i % mod * i % mod;
		res %= mod;
	}
	cout << res << endl;
	return 0;
}
