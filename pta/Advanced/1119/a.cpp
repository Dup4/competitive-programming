#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int n, rt, Unique, a[N], b[N], c[N];
vector <int> vec;
struct E {
	int son[2];
	E() { son[0] = son[1] = 0; }
}e[N];

int gao(int al, int ar, int bl, int br) {
	if (al > ar || bl > br) return 0;
	int rt = a[al];
	if (al == ar) return rt;
	if (a[al + 1] == b[br - 1]) {
		Unique = 0;
		e[rt].son[0] = gao(al + 1, ar, bl, br - 1);
	}
	else {
		int pos = -1;
		for (int i = al + 1; i <= ar; ++i) {
			if (a[i] == b[br - 1]) {
				pos = i;
				break;
			}
		}
		int lsze = pos - 1 - al;
		e[rt].son[0] = gao(al + 1, pos - 1, bl, bl + lsze - 1);
		e[rt].son[1] = gao(pos, ar, bl + lsze, br - 1);
	}
	return rt;
}

void getprint(int u) {
	if (!u) return;
	getprint(e[u].son[0]);
	vec.push_back(c[u]);
	getprint(e[u].son[1]);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(e, 0, sizeof e);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			c[i] = a[i];
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", b + i);
		}
		sort(c + 1, c + 1 + n);
		for (int i = 1; i <= n; ++i) {
			a[i] = lower_bound(c + 1, c + 1 + n, a[i]) - c;
			b[i] = lower_bound(c + 1, c + 1 + n, b[i]) - c;
		}
		vec.clear();
		Unique = 1;
		getprint(gao(1, n, 1, n));
		if (Unique) puts("Yes");
		else puts("No");
		for (int i = 0; i < n; ++i)
			printf("%d%c", vec[i], " \n"[i == n - 1]);
	}
	return 0;
}
