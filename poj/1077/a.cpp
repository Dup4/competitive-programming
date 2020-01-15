#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
#define pii pair<int, int>
#define fi first
#define se second
#define all(a) a.begin(), a.end()
const int maxn = 362880 + 10;
char s[30];
const int FAC[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };
struct node {
	int G[9];
	int value, index, vis;
	void cantor() {
		value = 0;
		for (int i = 0; i < 9; i++) {
			int smaller = 0;
			for (int j = i + 1; j < 9; j++) {
				if (G[i] > G[j])
					smaller++;
			}
			value += FAC[8 - i] * smaller;
		}
	}
}St, End;

void getend() {
	for (int i = 0; i < 9; i++)
		End.G[i] = i + 1;
	End.cantor();
	End.index = 8;
	End.vis = 1;
}

void input() {
	int len = strlen(s);
	for (int i = 0, pos = 0; i < len; i++) {
		if (isdigit(s[i]))
			St.G[pos++] = s[i] - '0';
		else if (s[i] == 'x') {
			St.G[pos++] = 9;
			St.index = pos - 1;
		}
	}
	St.cantor();
	St.vis = 0;
}

int Move[9][4] = {
	-1, 3,-1, 1,
	-1, 4, 0, 2,
	-1, 5, 1,-1,
	 0, 6,-1, 4,
	 1, 7, 3, 5,
	 2, 8, 4,-1,
	 3,-1,-1, 7,
	 4,-1, 6, 8,
	 5,-1, 7,-1,
};
int visit[2][maxn];
pii pre[2][maxn];
char dir_0[5] = "udlr";
char dir_1[5] = "durl";

bool ok(int x, int y) {
	if (x < 0 || x >= 3 || y < 0 || y >= 3)
		return false;
	return true;
}

void bfs() {
	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j < 2; j++)
			visit[j][i] = 0, pre[j][i].fi = -1;
	}
	queue <node> q[2]; q[0].push(St); q[1].push(End);
	visit[0][St.value] = 1; visit[1][End.value] = 1;
	while (!q[0].empty() || !q[1].empty()) {
		node u, v;
		if (q[0].size() < q[1].size()) { u = q[0].front(); q[0].pop(); }
		else { u = q[1].front(); q[1].pop(); }
		for (int i = 0; i < 4; i++) {
			int nindex = Move[u.index][i];
			if (nindex == -1) continue;
			v = u;
			v.index = nindex;
			swap(v.G[v.index], v.G[u.index]);
			v.cantor();
			if (visit[v.vis][v.value] == 0) {
				visit[v.vis][v.value] = 1;
				pre[v.vis][v.value].fi = u.value;
				pre[v.vis][v.value].se = i;
				if (visit[!v.vis][v.value]) {
					string ans = "";
					int tmp = v.value;
					while (pre[0][tmp].fi != -1) {
						ans += dir_0[pre[0][tmp].se];
						tmp = pre[0][tmp].fi;
					}
					reverse(all(ans));
					tmp = v.value;
					while (pre[1][tmp].fi != -1) {
						ans += dir_1[pre[1][tmp].se];
						tmp = pre[1][tmp].fi;
					}
					cout << ans << endl;
					return;
				}
				q[v.vis].push(v);
			}
		}
	}
	puts("unsolvable");
}

int main() {
	getend();
	while (gets(s) != NULL) {
		input();
		bfs();
	}
}

/*
	双向BFS  
	从起始状态 和 末状态分别开始搜索
	然后判断相遇

	相遇之后 就递归去找答案

	但是要注意的一个是 递归找起始状态的答案 是没问题的
	但是递归找末状态的答案 方向是相反的 
*/
