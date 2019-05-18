#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 510
#define pll pair <ll, ll>
#define fi first
#define se second
const int D = (int)1e9;
int n;
pll a[N];
ll b[N];
vector <pll> Test;

bool ok() {
	for (auto it : Test) {
		for (int i = 1; i <= n; ++i) {
			b[i] = it.fi * a[i].fi + it.se * a[i].se;
		}	
		bool flag = true;
		for (int i = 2; i <= n; ++i) {
			if (b[i] <= b[i - 1]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			return true;
		}
	}
	return false;
}

mt19937_64 rd(time(NULL));
int main() {
	int T; scanf("%d", &T);
	for (int i = 1; i <= 40000; ++i) {
		Test.emplace_back(rd() % D + 1, rd() % D + 1); 
	}
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d: ", kase);
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld%lld", &a[i].fi, &a[i].se);
		}
		sort(a + 1, a + 1 + n);
		int res = 0;
		do {
			if (ok()) {
				++res;
			}
		} while (next_permutation(a + 1, a + 1 + n));
		printf("%d\n", res);
	}
	return 0;
}
