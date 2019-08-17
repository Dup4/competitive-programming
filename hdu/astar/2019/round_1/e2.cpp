#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n, f[110];

ll gao(ll n) {
	if (n <= 101) return f[n];
	else {
		if (n % 2 == 0) {
			if ((n - 100) % 3 == 0)	return n - 1;
			return n / 2;
		} else {
			ll id = (n + 1) / 2;
			--id;
			ll res = 0;
			if (id % 3 == 0) {
				res = 4ll * (id / 3) + 1;
			} else {
				res = id / 3;
			}
			return res;
		}
	}
} 

int main() {
	f[1] = 1;
	for (int i = 2; i <= 101; ++i) {
		f[i] = 0;
		for (int j = 1; j < i; ++j) {
			f[i] += f[j] * j;
			f[i] %= i;
		}
	}
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int T; cin >> T;
	while (T--) {
		cin >> n;
		cout << gao(n) << "\n";
	}
	return 0;
}
