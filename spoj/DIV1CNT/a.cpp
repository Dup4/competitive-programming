#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 1e6 + 10;
int pri[N], check[N];
ll f[N], powd[N], sumd[N];
void sieve() {
	memset(check, 0, sizeof check);
	*pri = 0;
	f[1] = 1; powd[1] = 1; sumd[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++pri[0]] = i;
			f[i] = i + 1;
			sumd[i] = i + 1;
			powd[i] = i;
		}
		for (int j = 1; j <= *pri; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				powd[i * pri[j]] = powd[i] * pri[j];
				sumd[i * pri[j]] = sumd[i] + powd[i * pri[j]];  
				f[i * pri[j]] = f[i / powd[i]] * sumd[i * pri[j]];
				break;
			} else {
				sumd[i * pri[j]] = 1 + pri[j];
				powd[i * pri[j]] = pri[j];
				f[i * pri[j]] = f[i] * f[pri[j]];
			}
		}
	}
}

int main() {
	sieve(); 
	int _T; scanf("%d", &_T);
	while (_T--) {
		int n;
		scanf("%d", &n);
		int res = 0;
	//	for (int i = 1; i <= n; ++i) {
	//		cout << i << " " << f[i] << endl;
	//	}
		for (int i = 1; i <= n; ++i) res += f[i] - i;
		cout << res << endl;
	//	int res = 0;
	//	for (int i = 2; i <= n; ++i) {
	//		for (int j = 1; j < i; ++j) {
	//			if ((i % j == 0))
	//				res += j;
	//		}
	//	}
	//	for (int i = 1; i <= n; ++i) {
	//		for (int j = 1; j <= i; ++j) {
	//			res -= i / j;
	//		}
	//	}
	//	cout << res << endl;
	}
	return 0;
}
