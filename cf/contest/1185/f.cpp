#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define M 1010
#define pii pair <int, int>
#define fi first
#define se second
#define INF 0x3f3f3f3f
int n, m;
int a[M], has[N];
pii b[M], d[M]; 

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(a, 0, sizeof a);
		memset(b, 0x3f, sizeof b);
		memset(d, 0x3f, sizeof d);
		memset(has, 0, sizeof has);
		for (int i = 1, k, f, x; i <= n; ++i) {
			x = 0;
			scanf("%d", &k);
			while (k--) {
				scanf("%d", &f);
				x |= (1 << (f - 1));
			}	
			++a[x];
		}		
		for (int i = (1 << 9); i >= 1; --i) {
			for (int j = i - 1; j >= 0; --j) {
				if (((i | j) ^ i) == 0) {
					a[i] += a[j]; 
				}
			}
		}
		for (int i = 1, c, k, f, x; i <= m; ++i) {
			x = 0;
			scanf("%d %d\n", &c, &k);
			while (k--) {
				scanf("%d", &f);
				x |= (1 << (f - 1));
			}
			has[x] = 1;
			if (c < b[x].fi) {
				d[x] = b[x];
				b[x].fi = c;
				b[x].se = i;
			} else if (c < d[x].fi) {
				d[x].fi = c;
				d[x].se = i;
			}
		}
		int Max = 0, Min = 2e9 + 10, x = -1, y = -1;
	   	for (int i = 0; i < (1 << 9); ++i) {
			for (int j = i; j < (1 << 9); ++j) {
				if ((i == j && has[i] && d[i].fi != INF) ||
					(has[i] && has[j])) {
					int tot1, tot2, p, q;
					if (i == j) {
						tot1 = a[i];
						tot2 = b[i].fi + d[j].fi;
						p = b[i].se, q = d[j].se;
					} else {
						tot1 = a[i | j];
						tot2 = b[i].fi + b[j].fi;
						p = b[i].se; q = b[j].se; 
					}
					if (tot1 > Max ||
						(tot1 == Max && tot2 < Min)) {
						Max = tot1;
						Min = tot2;
						x = p;
						y = q;
					}	
				}
			}
		}	
		printf("%d %d\n", x, y);
	}
	return 0;
}
