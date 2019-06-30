#include <bits/stdc++.h>
using namespace std;

#define N 1010
int n, m;
int s[N];
struct node {
	int t, l, r;
	node() {}
	void scan() {
		scanf("%d%d%d", &t, &l, &r);
	}
}a[N];

bool ok(int l, int r) {
	for (int i = l; i <= r; ++i) {
		if (s[i] == 0) {
			return 1;
		}
	}
	return 0;
}

bool check(node a) {
	if (a.t == 1) {
		for (int i = a.l + 1; i <= a.r; ++i) {
			if (s[i - 1] > s[i]) {
				return 0;
			}
		}
		return 1;
	} else {
		for (int i = a.l + 1; i <= a.r; ++i) {
			if (s[i - 1] > s[i]) {
				return 1;
			}
		}
		return 0;
	}
}

void work() {
	memset(s, 0, sizeof s);
	for (int i = 1; i <= m; ++i) {
		if (a[i].t == 1) {
			++s[a[i].l];
			--s[a[i].r];
		}
	}
	for (int i = 1; i <= n; ++i) s[i] += s[i - 1];
	for (int i = 1; i <= n; ++i) {
		if (s[i]) s[i] = 1;
	}
	for (int i = 1; i <= m; ++i) {
		if (a[i].t == 0) {
			if (!ok(a[i].l, a[i].r)) {
				puts("NO");
				return;
			}
		}
	}
	int cnt = n;
	for (int i = 1; i <= n; ++i) {
		if (s[i] == 0) {
			s[i] = cnt;
			--cnt;
		}
	}
	for (int i = 1; i <= m; ++i) {
		if (!check(a[i])) {
			puts("NO");
			return;
		}
	}
	puts("YES");
	for (int i = 1; i <= n; ++i) printf("%d%c", s[i], " \n"[i == n]);
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= m; ++i) {
			a[i].scan();
		}	
		work();
	}
	return 0;
}
