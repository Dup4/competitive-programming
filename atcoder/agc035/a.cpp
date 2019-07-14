#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
int n, a[N];
map <int, int> mp;

int main() {
	while (scanf("%d", &n) != EOF) {
		mp.clear();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			++mp[a[i]];
		}
		vector <pii> vec;
		for (auto it : mp) vec.push_back(it);
		int sze = mp.size();
		if (sze == 1) {
			if (vec[0].fi == 0) {
				puts("Yes");
			} else {
				puts("No");
			}
		} else {
			if (n % 3) {
				puts("No");
			} else {
				if (sze == 2) {
					if ((vec[0].se == vec[1].se * 2 && vec[1].fi == 0) || (vec[0].se * 2 == vec[1].se && vec[0].fi == 0)) {
						puts("Yes");
					} else {
						puts("No");
					}
				} else if (sze == 3) {
					if (vec[0].se == vec[1].se && vec[0].se == vec[2].se && ((vec[0].fi ^ vec[1].fi) == vec[2].fi)) {
						puts("Yes");
					} else {
						puts("No");
					}
				} else {
					puts("No");
				}	
			}
		}
	}
	return 0;
}
