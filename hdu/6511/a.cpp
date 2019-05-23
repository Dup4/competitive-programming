#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1010
ll fac[20];
int n, m, arr[2][N]; 
struct qnode {
	int op;
	int a, b, c, d;
	void scan() {
		string s;
		cin >> s;
		op = (s == "min");
		cin >> s;
		a = (s == "b");
		cin >> b;
		cin >> s;
		c = (s == "b");
		cin >> d;
		//cout << op << " " << a << " " << b << " " << c << " " << d << "\n";
	}
}q[N];

int main() {
	fac[0] = 1;
	for (int i = 1; i <= 15; ++i) {
		fac[i] = fac[i - 1] * i;
	}
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	while (cin >> n >> m) {
		for (int i = 1; i <= m; ++i) {  
			q[i].scan();
		}
		ll res = 0;
		for (int j = 0; j < (1 << n); ++j) { 
			int x = 0;
			for (int i = 0; i < n; ++i) {
				arr[0][i + 1] = (j >> i) & 1;
				x += arr[0][i + 1];
			}
			for (int k = 1; k <= m; ++k) {
				// 0 max 1 min
				int a = q[k].a, b = q[k].b, c = q[k].c, d = q[k].d;    
				if (q[k].op == 0) {
					arr[1][k] = max(arr[a][b], arr[c][d]);
				} else {
					arr[1][k] = min(arr[a][b], arr[c][d]); 
				}
			}
			if (arr[1][m] == 1) {
				res += fac[x] * fac[n - x]; 
			}
		} 
		cout << res << "\n";
	}
	return 0;
}
