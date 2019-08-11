#include <bits/stdc++.h>
using namespace std;

#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
const int N = 2e3 + 10;
int n, k;
char s[N][N];
int x[N], y[N], dx[N];
int Gx[N][N];
int add[N], del[N];
int get(int i, int l, int r) {
	if (l > r) return 0;
	l = max(0, l - 1);
	return Gx[i][r] - Gx[i][l];
}
void run() {
	for (int i = 1; i <= n; ++i) {
		cin >> (s[i] + 1); 
	}
	x[0] = 0; y[0] = 0;
	for (int i = 1; i <= n; ++i) {
		bool F = 1; 
		for (int j = 1; j <= n; ++j) {
			if (s[i][j] == 'B') {
				F = 0;
				break;
			}
		}
		x[i] = x[i - 1] + F; 
	}
	for (int j = 1; j <= n; ++j) {
		bool F = 1;
		for (int i = 1; i <= n; ++i) {
			if (s[i][j] == 'B') {
				F = 0; 
				break;
			}
		}
		y[j] = y[j - 1] + F; 
	}
	for (int i = 1; i <= n; ++i) {
		Gx[i][0] = 0;
		for (int j = 1; j <= n; ++j) {
			Gx[i][j] = Gx[i][j - 1] + (s[i][j] == 'B');
		}
	}
	memset(add, 0, sizeof add);
	memset(del, 0, sizeof del);
	int res = 0, dy = 0;
	for (int j = 1; j <= k - 1; ++j) {
		int Max = 0, Min = 1e9; 
		for (int i = 1; i <= n; ++i) {
			if (s[i][j] == 'B') {
				Max = max(Max, i);
				Min = min(Min, i);
			} 
		}
		if (Max == 0) ++dy;
		else if (Max - Min <= k) {
			++add[max(1, Max - k + 1)];
			++del[Min + 1]; 
		}
	}
	for (int j = 1; j <= n - k + 1; ++j) {
		dx[0] = 0;
		for (int i = 1; i <= n; ++i) {
			dx[i] = dx[i - 1];
			if (get(i, 0, j - 1) + get(i, j + k, n) == 0) {
				++dx[i];
			}
		}
		int Max = 0, Min = 1e9; 
		for (int i = 1; i <= n; ++i) {
			if (s[i][j + k - 1] == 'B') {
				Max = max(Max, i);
				Min = min(Min, i);
			} 
		}
		if (Max == 0) ++dy;
		else if (Max - Min <= k) {
			++add[max(1, Max - k + 1)];
			++del[Min + 1]; 
		}
		int l = j, r = j + k - 1;
		for (int i = 1; i <= n; ++i) {
			int up = i, down = min(n, i + k - 1);
			dy += add[i] - del[i];
			res = max(res, y[l - 1] + y[n] - y[r] + x[up - 1] + x[n] - x[down] + dy + dx[down] - dx[up - 1]);
		}
		dy += del[n + 1]; 
		Max = 0, Min = 1e9; 
		for (int i = 1; i <= n; ++i) {
			if (s[i][j] == 'B') {
				Max = max(Max, i);
				Min = min(Min, i);
			} 
		}
		if (Max == 0) --dy;
		else if (Max - Min <= k) {
			--add[max(1, Max - k + 1)];
			--del[Min + 1];
		}	
	}
	cout << res << "\n";	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	while (cin >> n >> k) run();
	return 0;
}
