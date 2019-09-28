#include <bits/stdc++.h>
using namespace std;

using pII = pair <int, int>;
#define fi first
#define se second
int n; pII a[110]; char s[110];
int mon[] = {
	0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
bool operator < (pII a, pII b) {
	if (a.fi < b.fi || (a.fi == b.fi && a.se <= b.se)) {
		return true;
	}
	return false;
}
int dis(pII a, pII b) {
	if (a < b) {
		if (a.fi == b.fi) return b.se - a.se;
		int res = mon[a.fi] - a.se;
		for (int i = a.fi + 1; i < b.fi; ++i) res += mon[i];
		res += b.se;
		return res;
	} else {
		int res = mon[a.fi] - a.se; 
		for (int i = a.fi + 1; i <= 12; ++i) res += mon[i];
		for (int i = 1; i < b.fi; ++i) res += mon[i];
		res += b.se; 
		return res;
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%s %02d-%02d", s, &a[i].fi, &a[i].se);
		sort(a + 1, a + 1 + n, [&](pII x, pII y) {
			if (x.fi != y.fi) return x.fi < y.fi;
			return x.se < y.se;		
		});
		pII res = pII(-1, -1); int Max = -1;
		a[0] = a[n];
		int pos = 0;
		for (int i = 1; i <= 12; ++i) {
			for (int j = 1; j <= mon[i]; ++j) {
				pII t = pII(i, j);
				while (pos < n && a[pos + 1] < t) ++pos;
				if (dis(a[pos], t) > Max) {
					Max = dis(a[pos], t);
					res = t;
				} else if (dis(a[pos], t) == Max) {
					if (dis(pII(10, 28), t) < dis(pII(10, 28), res)) {
						res = t;
					}
				}
			}
		}
		printf("%02d-%02d\n", res.fi, res.se);
	}
	return 0;
}
