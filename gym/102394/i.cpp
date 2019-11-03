#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

long long cntt[100000 + 10];

int main() {
	int T;
	scanf("%d", &T);
	cntt[0] = 1;
	for (int i = 1; i <= 100000; ++i) cntt[i] = (cntt[i - 1] * 2) % MOD;
	while (T--) {
		int n;
		int x, max, flag;
		long long ans, q = 1, t = 0, cnt;
		scanf("%d", &n);
		if (n == 1) {
			scanf("%d", &x);
			if (x == 0) {flag = 0; ans = 1;}
			else flag = 1;
		}
		else {
			scanf("%d", &x); 
			if (x == 0) {
				flag = 0; ans = 0; max = x; q = 1; t = 0; cnt = 0;
				for (int i = 1; i <= n - 1; ++i) {
					scanf("%d", &x);
					if (flag == 0) {
						if (x > max) {
							++t; cnt += (x - max - 1);
							max = x;
							if (max > n - 1) flag = 1;
						}
						else if (x == max) {
							if (cnt > 0) {
								q = (q * cnt) % MOD;
								cnt--;		
							}
							else flag = 1;
						}
						else {
							flag = 1;
						}
					}
				}
			}
			else flag = 1;
		}
		//printf("f %d\n", flag);
		if (flag == 1) printf("0\n");
		else {
			ans = cntt[t] * q % MOD;
			printf("%lld\n", ans);
		}
	}
	return 0;
}
