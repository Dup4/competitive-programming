#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e2 + 10;

struct node {
	int x, y;
	node(){}
	node(int x, int y):x(x),y(y){}
};

int n, m, k, sz;
int mp[maxn][maxn];
int dis[20][maxn][maxn];
int dp[1 << 16][20];
int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
int vis[maxn][maxn];
vector<node>vec;

bool check(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > m || mp[x][y] == 1 || vis[x][y]) return false;
	else return true;
}

void BFS(int pos, int x, int y) {
	memset(vis, 0, sizeof vis);
	dis[pos][x][y] = 0;
	queue<node>q;
	q.push(node(x, y));
	vis[x][y] = 1;
	while(!q.empty()) {
		node st = q.front();
		q.pop();
		for (int i = 0; i < 4; ++i) {
			node now = st;
			now.x = st.x + dir[i][0];
			now.y = st.y + dir[i][1];
			if(check(now.x, now.y)) {
				q.push(now);
				dis[pos][now.x][now.x] = dis[pos][st.x][st.y] + 1;
				vis[now.x][now.y] = 1;
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &n, &m, &k);
	vec.push_back(node(1, 1));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			scanf("%d", &mp[i][j]);
			if(mp[i][j] == 2) {
				vec.push_back(node(i, j));
			}
		}
	}
	for (int i = 0, len = vec.size(); i < len; ++i) {
		BFS(i, vec[i].x, vec[i].y);
	}
	sz = vec.size() - 1;
	memset(dp, 0x3f, sizeof dp);
	for (int S = 0; S < (1 << sz); ++S) {
		if(S == 0) {
			for (int i = 0; i < sz; ++i) {
				dp[S | (1 << i)][i] = dis[0][vec[i + 1].x][vec[i + 1].y];
			}		
		} else {
			for (int i = 0; i < sz; ++i) if(S & (1 << i)){
				for (int j = 0; j < sz; ++j) {
					if (S & (1 << j)) continue;
					dp[S | (1 << j)][j] = min(dp[S | (1 << j)][j], dp[S][i] + dis[i + 1][vec[j + 1].x][vec[j + 1].y]);
				}
			}
		}
	}
	for (int i =1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cout << dis[0][i][j] << " ";
		}
		cout << endl;
	}
	int ans = 0;
	for (int S = 0; S < (1 << sz); ++S) {
		for (int i = 0; i < sz; ++i) {
			if(dp[S][i] <= k) {
				int cnt = 0;
				for (int j = 0; j < sz; ++j) {
					if(S & (1 << j)) cnt++;
				}
				ans = max(ans, cnt);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
