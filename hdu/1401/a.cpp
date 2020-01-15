#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define fi first
#define se second
const int maxn = (int)4e3 + 10;
const int MAXN = (int)1e2 + 10;
const int MOD = (int)1e9 + 7;

int readint() {
	int num; scanf("%d", &num);
	return num - 1;
}

struct node {
	pii G[4];
	int step, value, vis;
	bool operator == (const node& r)const {
		for (int i = 0; i < 8; i++)
			if (r.G[i] != G[i])
				return false;
		return true;
	}
	void tran() {
		value = 0;
		sort(G, G + 4, [](pii a, pii b) { if (a.fi == b.fi) return a.se < b.se; else return a.fi < b.fi; });
		for (int i = 0; i < 4; i++) value = value * 10 + G[i].fi, value = value * 10 + G[i].se;
	}
	void read(int l, int r) {
		for (int i = l; i < r; i++) { G[i].fi = readint(); G[i].se = readint();}
		step = 0; tran();
	}
}st, tar;

void init() {
	st.G[0].se = readint(); st.G[0].fi--; 
	st.read(1, 4); tar.read(0, 4);
	st.vis = 0; tar.vis = 1;
}

int Move[2][4][2] = {
	-1, 0,
	 1, 0,
	 0,-1,
	 0, 1,

	-2, 0,
	 2, 0,
	 0,-2,
	 0, 2,
};

bool ok(int x, int y) {
	if (x < 0 || x >= 8 || y < 0 || y >= 8)
		return false;
	return true;
}

void bfs() {
	if (st == tar) {
		puts("YES");
		return;
	}
	queue <node> q[2]; q[0].push(st); q[1].push(tar);
	map <int, pii> mp[2]; mp[0][st.value] = pii(1, 0); mp[1][tar.value] = pii(1, 0);
	while (!q[0].empty() && !q[1].empty()) {
		node u;
		if (q[0].size() < q[1].size()) { u = q[0].front(); q[0].pop(); }
		else { u = q[1].front(); q[1].pop(); }
		if (u.step >= 8) continue;
		map <pii, int> visit;
		for (int i = 0; i < 4; i++)
			visit[u.G[i]] = 1;
		for (int i = 0; i < 4; i++) {
			int x = u.G[i].fi, y = u.G[i].se;
			for (int j = 0; j < 4; j++) {
				int nx = x + Move[0][j][0];
				int ny = y + Move[0][j][1];
				if (ok(nx, ny)) {
					if (visit[pii(nx, ny)]) {
						nx = x + Move[1][j][0];
						ny = y + Move[1][j][1];
						if (ok(nx, ny) && visit[pii(nx, ny)] == 0) {
							node v = u;
							swap(v.G[i].fi, nx); swap(v.G[i].se, ny);
							v.step++; v.tran();
							if (mp[v.vis][v.value].fi == 0) {
								mp[v.vis][v.value] = pii(1, v.step);
								pii tmp = mp[v.vis ^ 1][v.value];
								if (tmp.fi == 1 && tmp.se + v.step <= 8) {
										puts("YES");
										return;
								}
								q[v.vis].push(v);
							}
						}
					} else {
						node v = u;
						swap(v.G[i].fi, nx); swap(v.G[i].se, ny);
						v.step++; v.tran();
						if (mp[v.vis][v.value].fi == 0) {
							mp[v.vis][v.value] = pii(1, v.step);
							pii tmp = mp[v.vis ^ 1][v.value];
							if (tmp.fi == 1 && tmp.se + v.step <= 8) {
								puts("YES");
								return;
							}
							q[v.vis].push(v);
						}
					}
				}
			}
		}
	}
	puts("NO");
	return;
}

int main() {
	while (scanf("%d", &st.G[0].fi) != EOF) {
		init(); bfs();
	}
}


