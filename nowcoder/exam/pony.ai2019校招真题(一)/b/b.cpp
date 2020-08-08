#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 10;
int n, m, cnt[30], tot[30];
char s[N], t[N];

bool ok() {
	for (int i = 0; i < 26; ++i) if (cnt[i] > tot[i]) return false;
	return true;
}

int main() {
	scanf("%d%d", &n, &m);
	scanf("%s%s", s + 1, t + 1);
	memset(cnt, 0, sizeof cnt);
	memset(tot, 0, sizeof tot);
	for (int i = 1; i <= n; ++i) ++tot[s[i] - 'a'];
	ll res = 0;
	int l = 1;
	for (int i = 1; i <= m; ++i) {
		++cnt[t[i] - 'a'];
		while (l <= i && !ok()) {
			--cnt[t[l] - 'a'];
			++l;
		}
		res += (i - l + 1);
	}
	printf("%lld\n", res);
	return 0;
}
