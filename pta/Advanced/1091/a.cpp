#include <bits/stdc++.h>
using namespace std;
int n, m, L, T, now, tot;
vector<vector<vector<int>>> G, vis;
int Move[][3] = {
	{0, 0, 1},
	{0, 0, -1},
	{0, 1, 0},
	{0, -1, 0},
	{1, 0, 0},
	{-1, 0, 0},
};

bool ok(int x, int y, int z) {
	if (x < 0 || x >= L || y < 0 || y >= n || z < 0 || z >= m || vis[x][y][z] || G[x][y][z] == 0) 
		return false;
	return true;
}

void dfs(int x, int y, int z) {
	if (vis[x][y][z]) return;
	vis[x][y][z] = 1;
	++now;
	for (int i = 0; i < 6; ++i) {
		int nx = x + Move[i][0];
		int ny = y + Move[i][1];
		int nz = z + Move[i][2];
		if (ok(nx, ny, nz)) {
			dfs(nx, ny, nz);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	while (cin >> n >> m >> L >> T) {
		vis = vector<vector<vector<int>>>(L + 10, vector<vector<int>>(n + 10, vector<int>(m + 10, 0)));
		G = vector<vector<vector<int>>>(L + 10, vector<vector<int>>(n + 10, vector<int>(m + 10, 0)));
		tot = 0;
		for (int i = 0; i < L; ++i) {
			for (int j = 0; j < n; ++j) {
				for (int k = 0; k < m; ++k) {
					cin >> G[i][j][k];
				}
			}
		}		
		for (int i = 0; i < L; ++i) {
			for (int j = 0; j < n; ++j) {
				for (int k = 0; k < m; ++k) {
					if (G[i][j][k] == 1 && vis[i][j][k] == 0) {
						now = 0;
						dfs(i, j, k);
						if (now >= T) {
							tot += now;
						}
					}
				}
			}
		}
	    cout << tot << "\n";	
	}
	return 0;
}
