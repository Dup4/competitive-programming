#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
#define pii pair <int, int>
#define fi first
#define se second
const ll p = 1e9 + 7; 
int n, m, q, a[N]; 
pii qrr[N];
int res[N], fl[N][22], fr[N][22];

template <class T1, class T2>
void add(T1 &x, T2 y) {
	x += y;
	if (x >= p) x -= p;
}

void solve(int l, int r, vector <int> vec) {
	if (l >= r || vec.empty()) return;	
	int mid = (l + r) >> 1;
	for (int i = l; i <= mid + 1; ++i) {
		for (int j = 0; j < m; ++j) {
			fl[i][j] = 0;
		}
	}
	for (int i = mid; i <= r; ++i) {
		for (int j = 0; j < m; ++j) {
			fr[i][j] = 0;
		}
	}
	fl[mid + 1][0] = 1;
	fr[mid][0] = 1;
	for (int i = mid; i >= l; --i) {
		for (int j = 0; j < m; ++j) {
			add(fl[i][j], fl[i + 1][j]);
			add(fl[i][j], fl[i + 1][(j - a[i] + m) % m]);
		}
	}
	for (int i = mid + 1; i <= r; ++i) {
		for (int j = 0; j < m; ++j) {
			add(fr[i][j], fr[i - 1][j]);
			add(fr[i][j], fr[i - 1][(j - a[i] + m) % m]);
		}
	}
	vector <int> vl, vr;
	for (auto it : vec) {
		int ql = qrr[it].fi, qr = qrr[it].se;
		if (ql <= mid && qr > mid) {
			ll ans = 0;
			for (int i = 0; i < m; ++i) {
				add(ans, 1ll * fl[ql][i] * fr[qr][(m - i) % m] % p);
			}
			res[it] = ans;
		} else if (qr <= mid) {
			vl.push_back(it);
		} else {
			vr.push_back(it);
		}
	}
	solve(l, mid, vl);
	solve(mid + 1, r, vr);
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), a[i] %= m;
		scanf("%d", &q);
		vector <int> vec;
		for (int i = 1; i <= q; ++i) {
			int &l = qrr[i].fi, &r = qrr[i].se;
			scanf("%d%d", &l, &r);
			if (l == r) {
				if (a[l] == 0) res[i] = 2;
				else res[i] = 1;
			} else {
				vec.push_back(i);
			}
		}  
		solve(1, n, vec);
		for (int i = 1; i <= q; ++i) {
			printf("%d\n", res[i]);
		}
	}
	return 0;
}
