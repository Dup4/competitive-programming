#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10;
int n, k;
ll f[N][1 << N][N * N];

bool ok(int S, int T) {
	int s[10], t[10];
	for (int i = 0; i < n; ++i) {
		s[i] = (S >> i) & 1;
		t[i] = (T >> i) & 1;
	}
	for (int i = 0; i < n; ++i) {
		if (s[i] && t[i]) return false;
		if (i && ((s[i] && s[i - 1]) || (t[i] && t[i - 1]))) return false;
		if (i < n - 1 && s[i] && t[i + 1]) return false;
	    if (i && s[i] && t[i - 1]) return false;	
	}
	return true;
}

int main() {
	cin >> n >> k;
	memset(f, 0, sizeof f);
	f[0][0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int S = 0; S < (1 << n); ++S) {
			for (int T = 0; T < (1 << n); ++T) {
				if (ok(S, T)) {
					int num = __builtin_popcount(T);
					for (int j = 0; j + num <= k; ++j) {
						f[i][T][j + num] += f[i - 1][S][j];
					}						
				}
			}
		}
	}
	ll res = 0;
	for (int S = 0; S < (1 << n); ++S)
		res += f[n][S][k];
	cout << res << endl;
	return 0;
}
