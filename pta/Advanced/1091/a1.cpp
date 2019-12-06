#include <bits/stdc++.h>
using namespace std;
const int N = 1e6;
int n, m, L, T, now, tot;
int G[N], vis[N];
int Move[][3] = {
	{0, 0, 1},
	{0, 0, -1},
	{0, 1, 0},
	{0, -1, 0},
	{1, 0, 0},
	{-1, 0, 0},
};

inline int id(int x, int y, int z) {
	++x, ++y, ++z;
	return (x - 1) * (n * m) + (y - 1) * m + z; 
}

bool ok(int x, int y, int z) {
	if (x < 0 || x >= L || y < 0 || y >= n || z < 0 || z >= m || vis[id(x, y, z)] || G[id(x, y, z)] == 0) 
		return false;
	return true;
}

struct E {
	int x, y, z;
	E() {}
	E(int x, int y, int z) : x(x), y(y), z(z) {}
};

void bfs(int x, int y, int z) {
	queue <E> que;
	que.emplace(x, y, z);
	while (!que.empty()) {
		x = que.front().x;
		y = que.front().y;
		z = que.front().z;
		que.pop();
		vis[id(x, y, z)] = 1;
		++now;
		for (int i = 0; i < 6; ++i) {
			int nx = x + Move[i][0];
			int ny = y + Move[i][1];
			int nz = z + Move[i][2];
			if (ok(nx, ny, nz)) {
				vis[id(nx, ny, nz)] = 1;
				que.emplace(nx, ny, nz);
			}
		}

	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m >> L >> T;
	memset(G, 0, sizeof G);
	memset(vis, 0, sizeof vis);
	tot = 0;
	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < m; ++k) {
				cin >> G[id(i, j, k)];
			}
		}
	}		
	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < m; ++k) {
				if (G[id(i, j, k)] == 1 && vis[id(i, j, k)] == 0) {
					now = 0;
					bfs(i, j, k);
					if (now >= T) {
						tot += now;
					}
				}
			}
		}
	}
	cout << tot << "\n";	
	return 0;
}
