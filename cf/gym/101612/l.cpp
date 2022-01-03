#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair <int, int>
#define fi first
#define se second  
vector <pii> res;

bool ok(ll x) {
	int cnt = 0;
	while (x) {
		cnt += x % 2;
		x /= 2;
	}
	return cnt == 1;
}

void File() {
	freopen("little.in", "r", stdin);
	freopen("little.out", "w", stdout);
}
int main() {
	File();
	ll n;
	while (scanf("%lld", &n) != EOF) {
		if (n == 1 || ok(n)) {
			puts("-1");
			continue;
		}
		res.clear(); 
		for (int i = 2; 1ll * i * i * i <= n; ++i) if (n % i == 0) {
			int a = i, b = i + 1; 
			ll tmp = n; 
			if (tmp % a == 0 && tmp % b == 0) {
				while (tmp && (tmp % a == 0 || tmp % b == 0)) {
					if (tmp % a == 0) {
						tmp /= a;
					}
					if (tmp % b == 0) {
						tmp /= b;
					}
				}
				if (tmp == 1) {
					res.emplace_back(a, b);
				}	
			}
			tmp = n;
			if (tmp % a == 0) {
				while (tmp % a == 0) {
					tmp /= a;
				}
				if (tmp == 1) {
					res.emplace_back(a, 0); 
				}
			}
		}
		for (int i = max(2, (int)sqrt(n) - 10), j = 0; i < n && j <= 20; ++i, ++j) {
			if (n == 1ll * i * (i + 1)) { 
				res.emplace_back(i, i + 1);
			} 
			if (n == 1ll * i * i) {
				res.emplace_back(i, 0); 
			}
		}
		sort(res.begin(), res.end());
		res.erase(unique(res.begin(), res.end()), res.end());
		int sze = res.size();
		printf("%d\n", sze + 1);
		printf("1 %lld\n", n);
		for (int i = 0; i < sze; ++i) {
			ll tmp = n;
			int a = res[i].fi, b = res[i].se;
			int c = 0, d = 0;
			while (tmp && tmp % a == 0) {
				tmp /= a;
				++c;
			}
			if (b != 0) {
				while (tmp && tmp % b == 0) {
					tmp /= b;
					++d;
				}
			}
			printf("%d", c + d);
			for (int j = 1; j <= c; ++j) {
				printf(" %d", a);
			}
			for (int j = 1; j <= d; ++j) {
				printf(" %d", b);
			}
			puts("");
		}
	}
	return 0;
}
