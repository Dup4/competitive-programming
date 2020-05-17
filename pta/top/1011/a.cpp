#include <bits/stdc++.h>
using namespace std;

int n, m;

struct P { 
	int x, y;
    void scan() { scanf("%d%d", &x, &y); }	
	bool operator == (const P &other) const {
		return x == other.x && y == other.y;
	}
}A[30], B[30];

void gao() {
	for (int i = 1; i <= n; ++i) {
		int j = (i + 1);
		if (j > n) j = 1;
		for (int k = 1; k <= m; ++k) {
			int o = (k + 1);
			if (o > m) o = 1;
			if ((A[i] == B[k] && A[j] == B[o]) ||
				(A[i] == B[o] && A[j] == B[k]) ) {
				puts("YES");
				return;
			}
		}
	}
	puts("NO");
}

int main() {
	int _T;
	scanf("%d", &_T);
	while (_T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) A[i].scan();
		scanf("%d", &m);
		for (int i = 1; i <= m; ++i) B[i].scan();
		gao();
	}
	return 0;
}
