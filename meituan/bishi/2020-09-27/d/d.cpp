#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e2 + 10;
constexpr int INF = 0x3f3f3f3f;
int n, m, sx, sy, ex, ey, a[N][N], b[N][N];
//, f[N][N];
int X[2], Y[2];

bool ok(int x, int y) {
	if (x < X[0] || x > X[1] || y < Y[0] || y > Y[1]) return false;
	return true;
}

struct node {
	int t, x, y;
	node() {}
	node(int t, int x, int y) : t(t), x(x), y(y) {}
	bool operator < (const node &other) const {
		return t > other.t;
	};
};

int limit;
bool bfs() {
	X[0] = sx, X[1] = ex;
	if (X[0] > X[1]) swap(X[0], X[1]);
	Y[0] = sy, Y[1] = ey;
	if (Y[0] > Y[1]) swap(Y[0], Y[1]);
//	memset(f, 0x3f, sizeof f);
//	f[sx][sy] = 0;
	queue <node> que;
	que.push(node(0, sx, sy));
	int res = INF, x, y, _a, _b, _t, tot, remind;
	while (!que.empty()) {
		node it = que.front(); que.pop();
		if (it.t >= res || it.t >= limit) continue;
		if (it.x == ex && it.y == ey) {
			res = it.t;
			continue;
		}
		x = it.x, y = it.y;
		_a = a[x][y];
		_b = b[x][y];
		_t = it.t;
		tot = _a + _b;
		remind = _t % tot;
		if (remind < _a) {
			//if (ex == x && _t + tot - remind < res) 
			if (_t + tot - remind < res) que.push(node(_t + tot - remind, x, y));
			if (ex > x && _t + 1 < res) que.push(node(_t + 1, x + 1, y));
			else if (ex < x && _t + 1 < res) que.push(node(_t + 1, x - 1, y));
		} else {
			//if (ey == y && _t + _a - remind < res) 
			if (_t + _a - remind < res) que.push(node(_t + _a - remind, x, y));
			if (ey > y && _t + 1 < res) que.push(node(_t + 1, x, y + 1));
			else if (ey < y && _t + 1 < res) que.push(node(_t + 1, x, y - 1));
		}	
	}
	if (res <= limit) {
		printf("%d\n", res);
		return true;
	}
	return false;
}

int main() {
	scanf("%d%d%d%d%d%d", &n, &m, &sx, &sy, &ex, &ey);
	for (auto &arr : {a, b}) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", arr[i] + j);
			}
		}
	}
	limit = 1;
	while (!bfs()) limit *= 2;
//	bfs();
	return 0;
}
