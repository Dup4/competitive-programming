#include <bits/stdc++.h>

using namespace std;

const int maxn = 60;

struct node {
	int x, y, pos;
	node(){}
	node(int x,int y, int pos):x(x), y(y), pos(pos){}
};

int n;
int arr[maxn][maxn];
int num[maxn], len;
int dir[4][2] = {1,0,0,1,-1,0,0,-1};

bool judge(int x) {
	len = 0;
	if(x == 0) {
		num[++len] = x;
	}
	while(x) {
		num[++len] = x % 10;
		x /= 10;
	}
	queue<node>q;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if(arr[i][j] == num[len]) {
				q.push(node(i, j, len));
			}
		}
	}
	while(!q.empty()) {
		node st = q.front();
		q.pop();
		if(st.pos == 1) {
			return true;
		}
		for (int i = 0; i < 4; ++i) {
			int dx = st.x + dir[i][0];
			int dy = st.y + dir[i][1];
			if(dx < 1 || dx > n || dy < 1 || dy > n){
				continue;
			}
			if(arr[dx][dy] != num[st.pos - 1]) continue;
			q.push(node(dx, dy, st.pos - 1));
		}
	}
	return false;
}

int main() {
	while(~scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				scanf("%d", &arr[i][j]);
			}
		}
		for (int x = 0; ; ++x) {
			if(!judge(x)) {
				printf("%d\n", x);
				break;
			}
		}
	}	
	return 0;
}
