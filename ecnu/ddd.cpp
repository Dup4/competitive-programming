#include <bits/stdc++.h>
using namespace std;

#define N 5000010
#define pii pair <int, int>
#define fi first
#define se second
int n, arr[N], s[N], res;
vector < vector <pii> > a, b;      
void solve() {
	for (int i = 1; i <= n; ++i) {
		int tot = 0;
		int j = 0, k = 0;
		if (!a[i].empty()) {
			reverse(a[i].begin(), a[i].end());
		}
		int sze[2] = {(int)a[i].size(), (int)b[i].size()};
		while (j < sze[0] || k < sze[1]) {
			++tot;
			pii it;
			if (j == sze[0] || (k < sze[1] && a[i][j].fi < b[i][k].fi)) {
				it = b[i][k];
				++k;
			} else {
				it = a[i][j];
				++j;
			}
			res = max(res, tot + s[it.fi - 1] + s[n] - s[it.se]);
		}
	}
}

void read(int &x) {
	x = 0; char c;
	while (!isdigit(c = getchar()));
	while (isdigit(c)) {
		x = x * 10 + c - '0';
		c = getchar();
	}
}

void init() {
	a.clear();
	a.resize(n + 1);
	b.clear();
	b.resize(n + 1);
}
int main() {
	while (scanf("%d", &n) != EOF) { 
		init();
		for (int i = 0; i <= n; ++i) {
			s[i] = 0;  
		}
		for (int i = 1; i <= n; ++i) {
			read(arr[i]);
			if (arr[i] == i) { 
				s[i] = 1;   
			}
			s[i] += s[i - 1]; 
			if (abs(arr[i] - i) % 2 == 0) {
				int mid = (arr[i] + i) >> 1;
			 	if (arr[i] > i) {
					a[mid].push_back(pii(i, arr[i]));
				} else {
					b[mid].push_back(pii(arr[i], i));
				}	
			}
		}
		res = s[n];
		solve();
		init();
		for (int i = 1; i <= n; ++i) {
			if (abs(arr[i] - i) % 2) {
				int mid = (arr[i] + i) >> 1;
				if (arr[i] > i) {
					a[mid].push_back(pii(i, arr[i]));
				} else {
					b[mid].push_back(pii(arr[i], i));
				}
			}
		}
		solve();
		printf("%d\n", res);
	}
	return 0;
}
