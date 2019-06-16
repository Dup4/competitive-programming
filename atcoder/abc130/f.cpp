#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, x[N], y[N]; 
char s[N][2]; 
vector <int> vec[4];
int mp[220];
int X[2], Y[2];

int main() {
	mp['R'] = 0;
	mp['L'] = 1;
	mp['U'] = 2;
	mp['D'] = 3;
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < 4; ++i) {
			vec[i].clear();
		}
		X[0] = 1e8 + 1, X[1] = -1e8 - 1;
		Y[0] = 1e8 + 1, Y[1] = -1e8 - 1;
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d%s", x + i, y + i, s[i] + 1);
			if (s[i][1] == 'R') {
				vec[0].push_back(x[i]); 
				Y[0] = min(Y[0], y[i]);
			    Y[1] = max(Y[0], y[i]);	
			} else if (s[i][1] == 'L') {
				vec[1].push_back(x[i]);
				Y[0] = min(Y[0], y[i]);
				Y[1] = max(Y[0], y[i]);
			} else if (s[i][1] == 'U') {
				vec[2].push_back(y[i]);
				X[0] = min(X[0], x[i]);
				X[1] = max(X[1], x[i]);	
			} else {
				vec[3].push_back(y[i]);
				X[0] = min(X[0], x[i]);
				X[1] = max(X[1], x[i]);
			}
		}
		
	}
	return 0;
}
