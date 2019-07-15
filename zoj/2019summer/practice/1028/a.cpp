#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair <ll, ll>
#define fi first
#define se second
#define N 1010
int n, m, q, s;
char G[N][N];
pll a[27][N][N], base[N][N]; 

void add(int id, int x1, int y1, int x2, int y2) {
	a[id][x2][y2].fi += 1;
	a[id][x2][y2].se += id;
	a[id][x1][y1].fi += 1;
	a[id][x1][y1].se += id;
	a[id][x1 - 1][y2].fi -= 1;
	a[id][x1 - 1][y2].se -= id;
	a[id][x2][y1 - 1].fi -= 1;
	a[id][x2][y1 - 2].se -= id;
}

pll query(pll a[][N], int x1, int y1, int x2, int y2) {
	pll res = pll(0, 0);
	res.fi = a[x2][y2].fi + a[x1][y1].fi - a[x1 - 1][y2].fi - a[x2][y1 - 1].fi;
	res.se = a[x2][y2].se + a[x1][y1].se - a[x1 - 1][y2].se - a[x2][y1 - 1].se;
	return res;  
}

struct qnode {
	int x[2], y[2];
	char c[10];
	qnode() {}
	void scan() {
		scanf("%d%d%d%d %s", x, y, x + 1, y + 1, c);
		add(c[0] - 'a', x[0], y[0], x[1], y[1]);
	}
}qrr[300010];

int main() {
	while (scanf("%d%d%d%d", &n, &m, &q, &s) != EOF) {
		memset(a, 0, sizeof a);
		for (int i = 1; i <= n; ++i) scanf("%s", G[i] + 1);
		for (int i = 1; i <= q; ++i) {
			qrr[i].scan();
		}
		for (int i = 0; i < 26; ++i) {
			for (int j = 1; j <= n; ++j) {
				for (int k = 1; k <= m; ++k) {
					a[i][j][k].fi += a[i][j - 1][k].fi + a[i][j][k - 1].fi - a[i][j - 1][k - 1].fi;
					a[i][j][k].se += a[i][j - 1][k].se + a[i][j][k - 1].se - a[i][j - 1][k - 1].se;
				}
			}
			for (int j = 1; j <= n; ++j) {
				for (int k = 1; k <= m; ++k) {
					a[i][j][k].fi += a[i][j - 1][k].fi + a[i][j][k - 1].fi - a[i][j - 1][k - 1].fi;
					a[i][j][k].se += a[i][j - 1][k].se + a[i][j][k - 1].se - a[i][j - 1][k - 1].se;
				}
			}
			for (int j = 1; j <= n; ++j) {
				for (int k = 1; k <= m; ++k) {
					a[i][j][k].fi += a[i - 1][j][k].fi;
					a[i][j][k].se += a[i - 1][j][k].se;
				}
			}
		}
		ll tot = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				int id = G[i][j] - 'a';
				base[i][j].fi = 1ll * id * a[id - 1][i][j].fi - a[id - 1][i][j].se + a[id + 1][i][j].se - 1ll * id * a[id + 1][i][j].fi;
				tot += base[i][j].fi;
				base[i][j].fi += base[i - 1][j].fi + base[i][j - 1].fi - base[i - 1][j - 1].fi;
			}
		}
		ll Min = 1e18; int pos = -1;
		for (int i = 1; i <= q; ++i) {
			int x[2] = {qrr[i].x[0], qrr[i].x[1]};
			int y[2] = {qrr[i].y[0], qrr[i].y[1]};
			int id = qrr[i].c[0] - 'a';
			ll now = tot - query(base, x[0], y[0], x[1], y[1]).fi;
		   	pll l = query(a[id - 1], x[0], y[0], x[1], y[1]);
			pll r = query(a[id + 1], x[0], y[0], x[1], y[1]);
			now += 1ll * id * l.fi - l.se - 1ll * id * r.fi + r.se;
			if (now < Min) {
				Min = now;
				pos = i;
			}
		}
		printf("%lld %d\n", Min, pos);
	}
	return 0;
}
