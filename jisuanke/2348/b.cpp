#include <bits/stdc++.h>
using namespace std;

/*
 	0 A 出现偶数次 B 出现偶数次
	1 A 出现偶数次 B 出现奇数次
	2 A 出现奇数次 B 出现偶数次
	3 A 出现奇数次 B 出现奇数次 
 	f[i][0] = 2 * f[i - 1][0] + f[i - 1][2] + f[i - 1][1] 
	f[i][1] = 2 * f[i - 1][1] + f[i - 1][3] + f[i - 1][0]
	f[i][2] = 2 * f[i - 1][2] + f[i - 1][0] + f[i - 1][3]
	f[i][3] = 2 * f[i - 1][3] + f[i - 1][1] + f[i - 1][2] 
 */

#define N 100010 
#define ll long long
const ll p = 1e9 + 7;
ll n;
char s[N];

struct node {
	ll a[4][4];
	node() {
		memset(a, 0, sizeof a);
	}
	node operator * (const node &other) const {
		node res = node();
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				for (int k = 0; k < 4; ++k) {
					(res.a[i][j] += a[i][k] * other.a[k][j] % p) %= p;
				}
			}
		}
		return res;
	}
}base, res;

ll b[][4] = {
	2, 1, 1, 0,
	1, 2, 0, 1,
	1, 0, 2, 1,
	0, 1, 1, 2
};

void qmod(ll n) {
	while (n) {
		if (n & 1) {
			res = res * base;
		}
		base = base * base;
		n >>= 1;
	}
}

int main() {
	while (scanf("%s", s + 1)) {
		if (strlen(s + 1) == 1 && s[1] == '0') {
			break;
		}
		ll n = 0;
		for (int i = 1, len = strlen(s + 1); i <= len; ++i) {
			n = n * 10 + s[i] - '0';
			n %= (p - 1);
		}
		base = node();
		res = node();
		res.a[0][0] = 1;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				base.a[i][j] = b[i][j];
			}
		}
		qmod(n);
		printf("%lld\n", res.a[0][0]);
	}	
	return 0;
}
