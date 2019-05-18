#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e4 + 10;

int n, q;
char str[maxn];

int main() {
	while(~scanf("%d %d", &n, &q)) {
		scanf("%s", str + 1);
		while(q--) {
			int l, r;
			scanf("%d %d", &l, &r);
			ll tmp = r - l + 1;
			printf("%lld\n", tmp * (tmp + 1) / 2);			
		}
	}
	return 0;
}
