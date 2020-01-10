#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
int n, x; ll W, w[100];
pII S[(1 << 21) + 10]; 

void gao() {
	if (w[n - 1] > W) {
		puts("No");
		return;
	}
	if (x >= n) {
		puts("Yes");
		return;
	}
	for (int i = 0; i < (1 << n); ++i) S[i] = pII(-1, 0);
	S[0] = pII(x, 0);
	for (int i = 0; i < (1 << n); ++i) {
		for (int j = 0; j < n; ++j) {
			if (((i >> j) & 1) == 0) {
				pII tmp = S[i];
				if (w[j] > tmp.se) {
					--tmp.fi;
					tmp.se = W - w[j];
				} else {
					tmp.se -= w[j];
				}
				S[i | (1 << j)] = max(S[i | (1 << j)], tmp);
			}
		}
	}
	if (S[(1 << n) - 1].fi >= 0) {
		puts("Yes");
	} else {
		puts("No");
	}
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d%d%lld", &n, &x, &W);
		for (int i = 0; i < n; ++i) scanf("%lld", w + i);
		sort(w, w + n);
		gao();
	}
	return 0;
}
