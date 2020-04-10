#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e3 + 10;
int n, m, A, B, q, a[N][N], b[N][N];

struct Hash2D { // 1-index
    static const ll px = 131, py = 233, mod = 998244353;
    static ll pwx[N], pwy[N];
    ll hv[N][N];
    static void init() {
        pwx[0] = pwy[0] = 1;
        for (int i = 1; i < N; ++i) {
            pwx[i] = pwx[i - 1] * px % mod;
            pwy[i] = pwy[i - 1] * py % mod;
        }
    }
    void init_hash(int n, int m, int a[][N]) {
		for (int i = 1; i <= n; ++i) {
			ll s = 0;
			for (int j = 1; j <= m; ++j) {
                s = (s * py + a[i][j]) % mod;
                hv[i][j] = (hv[i - 1][j] * px + s) % mod;
            }
        }
    }
    ll get(int x, int y, int dx, int dy) {
        --x; --y;
        ll ret = hv[x + dx][y + dy] + hv[x][y] * pwx[dx] % mod * pwy[dy]
                 - hv[x][y + dy] * pwx[dx] - hv[x + dx][y] * pwy[dy];
        return (ret % mod + mod) % mod;
    }
}ha, hb;
ll Hash2D::pwx[N], Hash2D::pwy[N];
vector <ll> vec;

int main() {
	Hash2D::init();
	vec.clear();
	while (scanf("%d%d%d%d", &n, &m, &A, &B) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%1d", a[i] + j);
			}	
		}
		ha.init_hash(n, m, a);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				int _i = i + A - 1;
				int _j = j + B - 1;
				if (_i <= n && _j <= m) {
					vec.push_back(ha.get(i, j, A, B));
				}
			}
		}
		sort(vec.begin(), vec.end());
		scanf("%d", &q);
		while (q--) {
			for (int i = 1; i <= A; ++i) {
				for (int j = 1; j <= B; ++j) {
					scanf("%1d", b[i] + j);
				}
			}
			hb.init_hash(A, B, b);
			ll val = hb.get(1, 1, A, B);
			int pos = lower_bound(vec.begin(), vec.end(), val) - vec.begin();
			puts(val == vec[pos] ? "1" : "0");
		}
	}	
	return 0;
}
