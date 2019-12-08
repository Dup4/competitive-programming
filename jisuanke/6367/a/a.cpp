#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 0x3f3f3f3f3f3f3f3f;

ll L, R, S;

ll gao(ll l, ll r) {
	if (l > r) return INF;
	ll res = 0;
	if (r - l + 1 <= 10) {
		for (ll i = l; i <= r; ++i) {
			res ^= i;
		}
	} else {
		ll ql = l, qr = r;
		while (ql % 4 != 0) {
			res ^= ql;
			ql++;
		}
		while (qr % 4 != 3) {
			res ^= qr;
			qr--;
		}
	}
	return res;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld %lld %lld", &L, &R, &S);
		ll res = -1;
		for (int i = 0; i <= 4; ++i) {
			for (int j = 0; j <= 4; ++j) {
				ll tmp = gao(L + i, R - j);
				if (tmp <= S) res = max(res, (R - j) - (L + i) + 1);
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
