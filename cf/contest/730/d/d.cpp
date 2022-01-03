#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define SZ(x) (int((x).size()))
const int N = 2e5 + 10;
int n; ll r, l[N], t[N];

int main() {
	scanf("%d%lld", &n, &r);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", l + i);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", t + i);
		if (l[i] > t[i]) {
			puts("-1");
			return 0;
		}
	}
	vector <ll> vec;
	int limit = 1e5;
	ll res = 0, pre = 0, T = 0;
	for (int i = 1; i <= n; ++i) {
		if (pre >= l[i]) {
			pre -= l[i];
			T += l[i];
			continue;
		}
		l[i] -= pre; 
		t[i] -= pre;
		T += pre;
		pre = 0;
		ll need = l[i] * 2 - t[i];
		if (need <= 0) {
			T += l[i] * 2;
		} else {
			ll cnt = need / r;
			ll mod = need % r;
			res += cnt;
			res += (mod > 0);
			for (ll j = 1, k = T; j <= cnt && SZ(vec) < limit; ++j, k += r) {
				vec.push_back(k);	
			}	
			T += r * cnt;
			l[i] -= r * cnt;
			l[i] -= mod;
			T += l[i] * 2;
			if (mod) {
				vec.push_back(T);
				pre = r - mod;
			}
			T += mod;
		}
	}
	printf("%lld\n", res); 
	if (res <= limit) {
		for (int i = 0; i < SZ(vec); ++i) {
			printf("%lld%c", vec[i], " \n"[i == SZ(vec) - 1]);
		}
	} else {
		puts("");
	}
	return 0;
}
