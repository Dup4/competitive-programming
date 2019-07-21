#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define M 10010
int n, a[M], cnt[M];
vector <vector<int>> vec, fac;
int prime[M], check[M], mu[M], tot;

void init() {
	tot = 0;
	memset(check, 0, sizeof check);
	mu[1] = 1;
	fac.clear();
	fac.resize(M);
	for (int i = 2; i < M; ++i) {
		if (!check[i]) {
			prime[++tot] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= tot; ++j) {
			if (1ll * i * prime[j] >= M) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			} else {
				mu[i * prime[j]] = -mu[i];
			}
		}
	}
	for (int i = 1; i < M; ++i) {
		for (int j = i; j < M; j += i) {
			fac[j].push_back(i);
		}
	}
}

int main() {
	init();
	while (scanf("%d", &n) != EOF) {
		vec.clear(); vec.resize(M);
		memset(cnt, 0, sizeof cnt);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			++cnt[a[i]];
			for (auto it : fac[a[i]]) {
				vec[it].push_back(a[i]);
			}
		}
		ll res = 0;
		for (int i = 1; i < M; ++i) {
			if (vec[i].empty() || mu[i] == 0) continue;
			ll tmp = 0;
			sort(vec[i].begin(), vec[i].end());
			vec[i].erase(unique(vec[i].begin(), vec[i].end()), vec[i].end());
			int sze = vec[i].size();
			for (auto it : vec[i]) { //枚举上边
				for (auto it2 : vec[i]) { //枚举腰
					if (it != it2 && cnt[it2] >= 2) {
						int pos = upper_bound(vec[i].begin(), vec[i].end(), it) - vec[i].begin();
						tmp += sze - pos;
					}
				}
			}
			for (auto it : vec[i]) {
				if (cnt[it] >= 3) {
					int pos = upper_bound(vec[i].begin(), vec[i].end(), it) - vec[i].begin();
					tmp += sze - pos;
					if (cnt[it] >= 4) ++tmp;
				}
			}
			res += tmp * mu[i];
		}
		printf("%lld\n", res);
	}
	return 0;
}
