#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10;

struct node {
	int x, y, step;

	node() {}
	
	node(int x, int y, int step): x(x), y(y), step(step) {}
}S, T;

int n, m;
string mp[N];
vector<vector<int> >vis;
int dir[6][2] = {1, 3, -1, 3, 1, -3, -1, -3, 2, 0, -2, 0};

bool ok(int x, int y, int xx, int yy) {
	if (x < 0 || x >= n || y < 0 || y >= m || mp[x][y] != ' ' || xx < 0 || xx >= n || yy < 0 || yy >= m) return false;
	else return true;
}

int gao() {
	queue<node> q;
	q.push(S);
	vis[S.x][S.y] = 1;
	while (!q.empty()) {
		node st = q.front();
		q.pop();
		if (st.x == T.x && st.y == T.y) return st.step;
		for (int i = 0; i < 6; ++i) {
			int dx = st.x + dir[i][0];
			int dy = st.y + dir[i][1];
			int nx = dx + dir[i][0];
			int ny = dy + dir[i][1];
			if (ok(dx, dy, nx, ny) && vis[nx][ny] == 0) {
				if (nx == T.x && ny == T.y) return st.step + 1;
				vis[nx][ny] = 1;
				q.push(node(nx, ny, st.step + 1));
			}
		}
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int _T;
	cin >> _T;
	while (_T--) {
		cin >> n >> m;
		n = 4 * n + 3, m = 6 * m + 3;
		vis.clear();
		vis.resize(n + 1);
		getline(cin, mp[0]);
		for (int i = 0; i < n; ++i) {
			getline(cin, mp[i]);
			int add = m - mp[i].size();
			for (int j = 0; j < add; ++j) {
				mp[i].push_back(' ');
			}
			//cout << mp[i] << " " << mp[i].size() << endl;
			for (int j = 0; j < m; ++j) {
				if (mp[i][j] == 'S') { S = node(i, j, 1); }
				if (mp[i][j] == 'T') { T = node(i, j, 0); }
				vis[i].push_back(0);
			}
		}
		cout << gao() << "\n";
	}
	return 0;
}
