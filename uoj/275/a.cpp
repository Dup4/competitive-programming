#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll p = 1e9 + 7;
void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
}
ll n, m; int K; 
//表示当前填了i位，第一个数是否到达n的上届，第二个数是否到达i的上届，第二个数是否到达m的上届
ll f[110][2][2];

void g(ll x, vector<int> &vec) {
	vec.clear();
	while (x) {
		vec.push_back(x % K);
		x /= K;
	}
}

int main() {
	ll inv2 = 5e8 + 4;
	int T; scanf("%d%d", &T, &K);
	while (T--) {
		scanf("%lld%lld", &n, &m); m = min(n, m);
		ll res = 0;
		res = ((m + 1) % p) * ((m + 2) % p) % p * inv2 % p + ((n - m) % p) * ((m + 1) % p) % p;
		res = (res % p + p) % p;
		vector <int> A, B;
		g(n, A); g(m, B);
		while (B.size() < A.size()) B.push_back(0);
		reverse(A.begin(), A.end());
		reverse(B.begin(), B.end());
		memset(f, 0, sizeof f);
		f[0][1][1] = 1;
		int Max = A.size();
		for (int i = 0; i < Max; ++i) {
			for (int j = 0; j < 2; ++j) {
				for (int k = 0; k < 2; ++k) {
					for (int p = 0; p <= (j ? A[i] : K - 1); ++p) {
						for (int q = 0; q <= (k ? B[i] : K - 1) && q <= p; ++q) {
							add(f[i + 1][j & (p == A[i])][k & (q == B[i])], f[i][j][k]);
						}
					}
				}
			}
		}
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				add(res, p - f[Max][i][j]);
		printf("%lld\n", res);
	}
	return 0;
}
