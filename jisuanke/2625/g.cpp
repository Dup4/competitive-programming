#include <bits/stdc++.h>
using namespace std;

#define N 60
#define pii pair <int, int>
#define fi first
#define se second
int n;
pii a[N]; 

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &a[i].fi, &a[i].se);
		}
		sort(a + 1, a + 1 + n);
		for (int i = 1; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				int S[3] = {a[i].fi, a[j].fi, a[n].fi};
				
			}
		}
		
	}
	return 0;
}
