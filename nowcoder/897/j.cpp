#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll l, r;
ll f[110][2][2];
ll g(ll x) {
	ll res = 0;
	for (int i = 63; i >= 0; --i) {
		if ((x >> i) & 1) {
			int pre = (x >> (i + 1)) & 1; 
			f[i][1][0] = 0;
			f[i][1][1] = 0;
			f[i][0][pre] = 1;
			f[i][0][pre ^ 1] = 0;
			for (int j = i - 1; j >= 0; --j) {
				for (int o = 0; o < 2; ++o) {
					for (int l = 0; l < 2; ++l) {
						if (o == 1) {
							f[j][o][l] = f[j + 1][l][0];
						} else {
							f[j][o][l] = f[j + 1][l][0] + f[j + 1][l][1];
						}
					}
				}
			}
			for (int j = 0; j < 2; ++j) {
				for (int k = 0; k < 2; ++k) {
					res += f[0][j][k];
				}
			}
			if (i < 62 && (((x >> (i + 2)) & 1)) == 1) {
				--res;
				break;
			}
		}
	}
	return res;
}


int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld", &l, &r);
		printf("%lld\n", g(r) - g(l - 1));
	}
	return 0;
}
