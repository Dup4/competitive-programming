#include <bits/stdc++.h>
using namespace std;

#define N 1010
int n, m;
int s[N], y[N], res[N]; 
struct node {
	int t, l, r;
	node() {}
	void scan() {
		scanf("%d%d%d", &t, &l, &r);
	}
	bool operator < (const node &other) const {
		return l < other.l;
	}
}a[N];

void work() { 
	for (int i = 1; i <= n; ++i) {
		if (s[i] && y[i]) {
			puts("NO");
			return;
		} else if (s[i]) {
			if (i == 1 || !s[i - 1]) {
				res[i] = 1; 
			}
		} else if (y[i]) {
		
		}
	}
	puts("YES");
	for (int i = 1; i <= n; ++i) printf("%d%c", res[i], " \n"[i == n]);
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= m; ++i) a[i].scan();
		memset(s, 0, sizeof s);
		memset(y, 0, sizeof y);
		for (int i = 1; i <= m; ++i) {
			if (a[i].t == 0) {
				++s[a[i].l];
				--s[a[i].r + 1];
			} else {
				++y[a[i].l];
				--y[a[i].r + 1];
			}
		}
		for (int i = 1; i <= n; ++i) {
			s[i] += s[i - 1];
			y[i] += y[i - 1];
		}
		work();
	}
	return 0;
}
