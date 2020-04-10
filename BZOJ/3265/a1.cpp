#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;

struct LP {
	static const ll INF = 0x3f3f3f3f3f3f3f3f;
	int n, m;
	vector <ll> v;
	vector <vector<ll> > a; 
	LP(const vector<vector<ll> > &_a, int _n, int _m) {
		a = _a; n = _n; m = _m;
		v.resize(m + 1);
	}
	void pivot(int x, int y) {
	    int tp = 0;
	    for (int i = 0; i <= m; i++) if (a[x][i]) v[++tp] = i;
	    for (int i = 0;i <= n; i++) {
			if (i != x && a[i][y]) {
			    ll k = a[i][y]; a[i][y] = 0;
			    for (int j = 1; j <= tp; j++)
					a[i][v[j]] -= k * a[x][v[j]];
			}
		}
	}
	ll solve() {
	    a[n + 1][0] = INF; 
	    while(1) {
			int x = 0, y = n + 1;
			for (int i = 1; i <= m; i++)
			    if (a[0][i] > 0) { x = i; break; }
			if (!x) return -a[0][0];
			for (int i = 1; i <= n; i++)
			    if(a[i][x] > 0 && a[i][0] < a[y][0]) y = i;
			pivot(y,x);
	    }
	}
};

const int N = 1e3 + 10;
int n, m, a[N];

int main() {	
	while (scanf("%d%d", &n, &m) != EOF) {
		vector <vector<ll> > A(m + 2, vector <ll>(n + 2, 0)); 
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), A[0][i] = a[i];
		for (int i = 1, cnt, l, r, c; i <= m; ++i) {
			scanf("%d", &cnt);
		//	cnt = 1; 
			while (cnt--) {
				scanf("%d%d", &l, &r);
				for (int j = l; j <= r; ++j) {
					A[i][j] = 1;	
				}
			}
			scanf("%d", &c);
			A[i][0] = c;
		}
		LP lp(A, m, n);
		printf("%lld\n", lp.solve());
		for (int i = 1; i <= n; ++i)
			printf("%lld\n", lp.a[i][0]);
	}
	return 0;
}

