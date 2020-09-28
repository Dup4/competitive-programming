#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll p = 100;
int y, m, d, h, mm, s;
int mon[][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};
bool ok(int y) {
	if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) {
		return 1;
	} else {
		return 0;
	}
}

int main() {
	int T; cin >> T;
	while (T--) {
		scanf("%d-%d-%d %d:%d:%d", &y, &m, &d, &h, &mm, &s);
	   	int id = ok(y);	
		if (y == 2050) {
			puts("0");
			continue;
		}
		ll res = 0;
		for (int i = y; i < 2050; ++i) {
			res = (res + (ok(i) ? 366 : 365) * 86400 % p) % p;
		}
		ll tot = (s + mm * 60 % p + h * 3600 % p) % p; 
		for (int i = 1; i < m; ++i) {
			tot = (tot + mon[id][i] * 86400 % p) % p;
		}
		tot = (tot + (d - 1) * 86400 % p) % p;
		res = (res - tot + p) % p;
		printf("%lld\n", res);
	}
	return 0;
}
