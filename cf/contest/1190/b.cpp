#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define ll long long
#define fi first
#define se second
int n, a[N];
ll sum, tot;
map <int, int> mp;
bool ok() {
	mp.clear();
	for (int i = 1; i <= n; ++i) {
		++mp[a[i]];
		if (mp[a[i]] > 2) return 0;
	}
	int cnt = 0;
	for (auto it : mp) {
		if (it.se == 2) {
			++cnt;
		}
	}
	if (cnt == 1) {
		for (auto it : mp) {
			if (it.se == 2) {
				if (it.fi == 0 || mp.find(it.fi - 1) != mp.end()) {
					return 0;
				}
			}
		}
	}
	return cnt <= 1;
}

int main() {
	char *fi = "sjfnb";
	char *se = "cslnb";
	while (scanf("%d", &n) != EOF) {
		sum = 0, tot = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			sum += a[i];
			tot += i - 1;
		}
		if (sum == 0 || !ok()) {
			puts(se);
		} else {
			ll res = sum - tot;
			puts(res & 1 ? fi : se);
		}
	}
	return 0;
}
