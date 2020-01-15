#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 1e4 + 10, INF = 0x3f3f3f3f;
int s, t, limit, check[N], dis[N], bit[10]; 
void sieve() {
	memset(check, 0, sizeof check);
	for (int i = 2; i < N; ++i) {
		if (check[i] == 0) {
			for (int j = i * 2; j < N; j += i) {
				check[j] = 1;
			}
		}
	}
}

int f(int num, int i, int x) {
	return (num / bit[i] * 10 + x) * bit[i - 1] + num % bit[i - 1]; 
}

void bfs() {
	queue <pII> que;
	que.push(pII(s, 0));
	if (s == t) {
		puts("0");
		return;
	}
	while (!que.empty()) {
		pII u = que.front(); que.pop();
		for (int i = 1; i <= 4; ++i) {
			int j = (i == 4) ? 1 : 0;
			for (; j < 10; ++j) {
				int x = f(u.fi, i, j); 
				if (check[x] == 0 && u.se < dis[x]) {
					dis[x] = u.se + 1;
					if (x == t) {
						printf("%d\n", u.se + 1);
						return;
					}
					if (u.se < 10) {
						que.push(pII(x, u.se + 1));
					}
				}
			}
		}
	}
	puts("Impossible");
}

void gao() {
	bfs();
}


int main() {
	bit[0] = 1; bit[1] = 10; bit[2] = 100; bit[3] = 1000; bit[4] = 10000;
	sieve();
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d%d", &s, &t);
		memset(dis, 0x3f, sizeof dis);
		gao();
	}
	return 0;
}
