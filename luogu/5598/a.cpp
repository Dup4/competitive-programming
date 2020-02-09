#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 5e5 + 10; 
int n, p, nx[N], C[10][10]; ll a[N];
int tmp[70];
vector <vector<pII>> b(N);

int main() {
	while (scanf("%d%d", &n, &p) != EOF) {
		memset(C, 0, sizeof C);
		C[0][0] = 1;
		for (int i = 1; i <= p; ++i) {
			C[i][0] = C[i][i] = 1;
			for (int j = 1; j < i; ++j) {
				C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % p;
			}
		}
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i); 
		nx[n + 1] = n + 1;
		a[n + 1] = 0;
		for (int i = n; i >= 1; --i) {
			if (a[i + 1]) nx[i] = i + 1;
			else nx[i] = nx[i + 1]; 
		}
		for (int i = 1; i <= n; ++i) {
			b[i].clear(); 
			ll t = a[i];
			for (int j = 0; j <= 65 && t; ++j) {
				if (t % p) b[i].push_back(pII(t % p, j)); 
				t /= p;
			}
		}
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			int pre = i; 
			int ans = 1;
			memset(tmp, 0, sizeof tmp);
			while (pre <= n) {
				int Nx = nx[pre];
				int ok = 1;
				int tans = 1;
				for (auto &it : b[pre]) {
					tmp[it.se] += it.fi;
					if (tmp[it.se] >= p) {
						ok = 0;
						break;
					}
					tans = tans * C[tmp[it.se]][it.fi] % p;
				}
				if (!ok) break;
				ans = ans * tans % p;
				res += 1ll * (Nx - pre) * ans;
				pre = Nx;
			}
		}	
		printf("%lld\n", res);	
	}
	return 0;
}
