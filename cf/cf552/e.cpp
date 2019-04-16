#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, k, a[N], b[N], f[N];
set <int > se;

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		memset(f, 0, sizeof f);
		se.clear(); 
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			b[a[i]] = i;
		    se.insert(i);	
		}
		int id = 1, pos = n;
		while (!se.empty()) {
			while (f[b[pos]]) {
				--pos; 
			}
			f[b[pos]] = id;
			se.erase(b[pos]);
			int t = k;
			while (!se.empty() && t--) {
				int it = b[pos];
				auto po = se.upper_bound(it);
				if (po == se.begin()) {
					break;
				} else {
					po = prev(po);
					it = *po;
					se.erase(po);
					f[it] = id; 
				}
			}	
			t = k;
			while (!se.empty() && t--) {
				int it = b[pos];
				auto po = se.upper_bound(it);
				if (po == se.end()) {
					break;
				} else {
					it = *po;
					se.erase(po);
					f[it] = id;
				}
			}

			if (id == 1) {
				id = 2;
			} else {
				id = 1;
			}
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d", f[i]);
		}
		puts("");
	}
	return 0;
}
