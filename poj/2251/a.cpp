#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 3e1 + 5;
int G[maxn][maxn][maxn];
int v[maxn][maxn][maxn];
int sx, sy, sz, ex, ey, ez;
int Move[6][3] {
	1, 0, 0,
   -1, 0, 0,
	0, 1, 0,
	0,-1, 0,
	0, 0, 1,
	0, 0,-1,
};

struct node {
	int x, y, z;
	int step;
};

int ans;

int c, n, m;

bool ok(int x, int y, int z) {
	if (x < 0 || x >= c || y < 0 || y >= n || z < 0 || z >= m || G[x][y][z] || v[x][y][z])
		return false;
	return true;
}

void bfs() {
	node tmp;
	tmp.x = sx;
	tmp.y = sy;
	tmp.z = sz;
	tmp.step = 0;
	queue <node> q;
	q.push(tmp);
	v[sx][sy][sz] = 1;
	while (!q.empty()) {
		node u = q.front(), V;
		q.pop();
		if (u.x == ex && u.y == ey && u.z == ez) {
			ans = u.step;
			return;
		}
		for (int i = 0; i < 6; i++) {
			V.x = u.x + Move[i][0];
			V.y = u.y + Move[i][1];
			V.z = u.z + Move[i][2];
			if (ok(V.x, V.y, V.z))
			{
				V.step = u.step + 1;
				q.push(V);
				v[V.x][V.y][V.z] = 1;
			}
		}
	}
}

int main() {
	while (scanf("%d%d%d", &c, &n, &m) && (c || n || m)) {
		memset(G, 0, sizeof G);
		memset(v, 0, sizeof v);
		string s;
		for (int i = 0; i < c; i++) {
			for (int j = 0; j < n; j++) {
				cin >> s;
				for (int k = 0; k < m; k++) {
					if (s[k] == 'S') {
						sx = i;
						sy = j;
						sz = k;
						G[i][j][k] = 0;
					}
					else if (s[k] == 'E') {
						ex = i;
						ey = j;
						ez = k;
						G[i][j][k] = 0;
					}
					else if (s[k] == '.')
						G[i][j][k] = 0;
					else if (s[k] == '#')
						G[i][j][k] = 1;
				}
			}
		}
		ans = -1;
		bfs();
		if (ans == -1)
			printf("Trapped!\n");
		else
			printf("Escaped in %d minute(s).\n", ans);
	}
}
