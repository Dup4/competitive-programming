#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2100;

template <typename T>
struct BIT_2D {
	int n, m;
	T a[N][N][4];
	void init(int _n, int _m) { memset(a, 0, sizeof a); n = _n, m = _m; }
	void update(int x, int y, T v) {
		for (int i = x; i <= n; i += i & -i)
			for (int j = y; j <= m; j += j & -j) {
				a[i][j][0] += v;
				a[i][j][1] += v * x;
				a[i][j][2] += v * y;
				a[i][j][3] += v * x * y;
			}
	}
	T query(int x, int y) {
		T res = 0;
		for (int i = x; i; i -= i & -i)
			for (int j = y; j; j -= j & -j) {
				res += a[i][j][0] * (x + 1) * (y + 1);
				res -= a[i][j][1] * (y + 1);
				res -= a[i][j][2] * (x + 1);
				res += a[i][j][3];
			}
		return res;
	}
	void update(int x[], int y[], T val) {
		int dx[4] = { x[0], x[1] + 1, x[0], x[1] + 1 };
		int dy[4] = { y[0], y[1] + 1, y[1] + 1, y[0] };
		T v[4] = { val, val, -val, -val };
		for (int i = 0; i < 4; ++i)
			update(dx[i], dy[i], v[i]);
	}
	T query(int x[], int y[]) {
		int dx[4] = { x[0] - 1, x[1], x[0] - 1, x[1] };
		int dy[4] = { y[0] - 1, y[1], y[1], y[0] - 1 };
		T v[4] = { 1, 1, -1, -1 };
		T res = 0;
		for (int i = 0; i < 4; ++i)
			res += v[i] * query(dx[i], dy[i]);
		return res;
	}
};
BIT_2D <ll> bit; 

int main() {
	int n, m, x[2], y[2], op; ll v;
	scanf("%d%d", &n, &m);
	bit.init(n, m);
	while (scanf("%d%d%d%d%d", &op, x, y, x + 1, y + 1) != EOF) {
		if (op == 1) {
			scanf("%lld", &v);
			bit.update(x, y, v);
		} else {
			printf("%lld\n", bit.query(x, y));
		}
	}	
	return 0;
}
